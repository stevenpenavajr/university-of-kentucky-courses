// Client
// Secret Key found from server

// Includes
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/stat.h>
#include <fstream>
#include <arpa/inet.h>
#include <algorithm>
#include <map>
#include <errno.h>
#include <vector>
#include <ctype.h>
#include <fstream>
#include <sys/param.h>
#include <cstddef>
#include <sstream>

#define MAXARGS 128

void error(const char* message);
void printSep();
void evaluate(char* c);
int getRequestType(char* name);

extern "C" {
    #include "csapp.h"
}

// Print error function
void error(const char *msg) {
    perror(msg);
    exit(0);
}

// Printing a separator
void printSep() {
    printf("%s\n", "-----------------------------");
}

typedef struct request_struct {
    uint32_t secret;
    uint32_t type;
    int fileCt;
    char filename[80];
    uint32_t size;
    int status;
    char filedata[100000];
} request;

// Getting request integer type
int getRequestType(const char* name) {
    if (strncmp(name, "cput", 4) == 0) {
        return 1;
    }
    else if (strncmp(name, "cget", 4) == 0) {
        return 2;
    }
    else if (strncmp(name, "cdelete", 7) == 0) {
        return 3;
    }
    else if (strncmp(name, "clist", 5) == 0) {
        return 4;
    }
    else {
        return 0;
    }
}

// Getting argv
void parseLine(char* buf, char** argv, int& argc)
{
    char* delim;

    buf[strlen(buf) - 1] = ' ';
    while (*buf && (*buf == ' ')) {
        buf++;
    }

    argc = 0;
    while ((delim = strchr(buf, ' '))) {
        argv[argc++] = buf;
        *delim = '\0';

        buf = delim + 1;
        while (*buf && (*buf == ' ')) {
            buf++;
        }
    }
    argv[argc] = NULL;
}

// Doing client actions...
void evaluate(char* comline, int client_fd, request requ) {

    char* args[MAXARGS]; /* holds argument list */
    char buf[MAXLINE]; /* modified command line */
    int argc = 0;
    strcpy(buf, comline);
    parseLine(buf, args, argc);

    if (args[0] == NULL) {
        return; /* ignore empty line */
    }

    /* putting a file */
    if (strcmp(args[0], "cput") == 0) {

        if (argc == 2) {
            FILE* fileToSend;
            fileToSend = fopen(args[1], "rb");

            if (fileToSend == NULL) { 
                printf("%s\n", "File not found."); /* ensuring the file exists in the directory */
            } else {
                struct stat fileStat;
                if (stat(args[1], &fileStat) != 0) {
                    printf("%s\n", "Error.");
                } else {
                    /* getting size */
                    uint32_t fileSize = uint32_t(fileStat.st_size);

                    if (fileSize <= 100000) {
                        // good - do everything here

                        /* send type */
                        char const* cput = "cput";
                        requ.type = htonl(getRequestType(cput));
                        Rio_writen(client_fd, &requ.type, 4);

                        /* send secret key (key already in NWBO) */
                        Rio_writen(client_fd, &requ.secret, 4);

                        /* get response from server for key */
                        Rio_readn(client_fd, &requ.status, 4);
                        int statusCode = ntohl(requ.status);
                        if (statusCode == -1) {
                            printf("%s\n", "Response: file not sent due to incorrect key. Quit and try again.");
                            return;
                        } else {

                            /* putting filename in struct */
                            strcpy(requ.filename, args[1]);
                            Rio_writen(client_fd, &requ.filename, 80);

                            /* sending size */
                            fileSize = htonl(fileSize); /* putting size in NWBO */
                            requ.size = fileSize;
                            Rio_writen(client_fd, &requ.size, 4);

                            /* sending file data */
                            fread(requ.filedata, 100000, 92 + ntohl(fileSize), fileToSend); /* putting file's data into char buffer */
                            Rio_writen(client_fd, &requ.filedata, 92 + ntohl(fileSize));   

                            /* getting response */
                            Rio_readn(client_fd, &requ.status, 4);
                            requ.status = ntohl(requ.status);
                            if (requ.status == 0) {
                                printf("%s\n", "Response: file sent to server successfully.");
                            } else {
                                printf("%s\n", "Response: server did not get file.");
                            }

                        }
                    } else {
                        printf("%s\n", "That file is too big. Try again.");
                    }
                }
            }
        } else {
            printf("%s\n", "usage: cput <file name>");
        }

    }

    /* getting a file */
    else if (strcmp(args[0], "cget") == 0) {

        if (argc == 2) {
            
            /* send type */
            char const* cget = "cget";
            requ.type = htonl(getRequestType(cget));
            Rio_writen(client_fd, &requ.type, 4);

            /* send secret key (key already in NWBO) */
            Rio_writen(client_fd, &requ.secret, 4);

            /* read response */
            Rio_readn(client_fd, &requ.status, 4);
            
            if (ntohl(requ.status == -1)) {
                printf("%s\n", "Response: file not received due to incorrect key. Quit and try again.");
                return;
            }

            /* send file name we want */
            /* putting filename in struct first */
            strcpy(requ.filename, args[1]);
            Rio_writen(client_fd, &requ.filename, 80);

            /* getting file existence */
            Rio_readn(client_fd, &requ.status, 4);
            int success = ntohl(requ.status);

            /* continue here if success */
            if (success != -1) {
                
                /* reading size */
                Rio_readn(client_fd, &requ.size, 4);
                printf("Response: received file size: %i bytes.\n", ntohl(requ.size));

                /* reading data */
                if (ntohl(requ.size) <= 100000) {
                    Rio_readn(client_fd, &requ.filedata, 7 + ntohl(requ.size));
                    FILE* receivedFileData = fopen (requ.filename, "wb");  
                    fwrite (requ.filedata , sizeof(char), ntohl(requ.size), receivedFileData);
                    printf("%s\n", "Response: received file data.");
                    requ.status = htonl(0);
                    Rio_writen(client_fd, &requ.status, 4);
                    fclose (receivedFileData);   
                } else {
                    printf("%s\n", "That file is too big. Try again.");
                }
            } else {
                printf("%s\n", "That file was not found on the server.");
            }


        } else {
            printf("%s\n", "usage: cget <file name>");
        }

    }

    /* listing files */
    else if (strcmp(args[0], "clist") == 0) {

        if (argc == 1) {

            /* send type */
            char const* clist = "clist";
            requ.type = htonl(getRequestType(clist));
            Rio_writen(client_fd, &requ.type, 4);
            
            /* send secret key (key already in NWBO) */
            Rio_writen(client_fd, &requ.secret, 4);

            /* process key */
            Rio_readn(client_fd, &requ.status, 4);

            if (ntohl(requ.status) != 0) {
                printf("%s\n", "Response: files not listed due to incorrect key. Quit and try again.");
                return;
            } else {

                /* receive number of files */
                Rio_readn(client_fd, &requ.fileCt, 4);
                printf("Response: %i files in the current directory.\n", ntohl(requ.fileCt));
                printf("├── current directory:\n");
                /* receive file names */
                for (uint32_t i = 0; i < ntohl(requ.fileCt); i++) {
                    Rio_readn(client_fd, &requ.filename, 80);
                    printf("│   └── %s\n", requ.filename);;
                }

            }


            
            
        } else {
            printf("%s\n", "usage: clist");
        }

    }

    /* deleting a file */
    else if (strcmp(args[0], "cdelete") == 0) {

        if (argc == 2) {
            
            /* send type */
            char const* cdelete = "cdelete";
            requ.type = htonl(getRequestType(cdelete));
            Rio_writen(client_fd, &requ.type, 4);

            /* send secret key (key already in NWBO) */
            Rio_writen(client_fd, &requ.secret, 4);

            /* read response */
            Rio_readn(client_fd, &requ.status, 4);
            
            if (ntohl(requ.status == -1)) {
                printf("%s\n", "Response: file not deleted due to incorrect key. Quit and try again.");
                return;
            }

            /* send file name we want */
            strcpy(requ.filename, args[1]);
            Rio_writen(client_fd, &requ.filename, 80);

            /* read response */
            Rio_readn(client_fd, &requ.status, 4);
            
            if (ntohl(requ.status == -1)) {
                printf("%s\n", "Response: file not found on server.");
            } else {
                printf("%s\n", "Response: file deleted successfully.");
            }

        } else {
            printf("%s\n", "usage: cdelete <file name>");
        }

    }

    /* quit program */
    else if (strcmp(args[0], "quit") == 0) {
        if (argc == 1) {
            close(client_fd);
            printf("%s\n", "Goodbye.");
            exit(0);
        } else {
            printf("%s\n", "usage: quit");
        }
    }

    /* invalid command */
    else {
        printf("%s\n", "That isn't a valid command.");
    }
}

// Driver
int main(int argc, char *argv[])
{
    /* intro */
    printSep();
    printf("%s\n", "Welcome to the myCloud client.");

    /* checking arguments */
    if (argc != 4) {
        fprintf(stderr, "%s\n", "usage: ./mycloudclient <server> <port> <key>");
        exit(0);
    }

    /* initializing port, socket, rio object, and request object */
    int clientfd, portno;
    rio_t rio;
    request req;

    /* parsing args */
    portno = atoi(argv[2]);
    req.secret = htonl(atoi(argv[3])); /* secret in network byte order */

    /* attempting connection with host and port */
    clientfd = Open_clientfd(argv[1], portno);
    Rio_readinitb(&rio, clientfd);

    /* if code here is reached, connection is successful */
    printSep();
    printf("%s\n", "Connected!");

    /* telling user what they can do */
    printf("%s", "Possible operations:");
    printf(" %s\n", "cget, cput, clist, cdelete");
    printSep();

    /* repeated user input */
    char cmdline[MAXLINE];
    while (1) {
        printf("%s", "--> ");
        fgets(cmdline, MAXLINE, stdin);
        if (feof(stdin)) {
            close(clientfd);
            printf("\n%s\n", "Goodbye.");
            exit(0);
        }
        evaluate(cmdline, clientfd, req);
    }

    close(clientfd);
    exit(0);

}



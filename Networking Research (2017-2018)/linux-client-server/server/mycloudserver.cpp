// Server

// Includes
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <dirent.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <vector>

extern "C" {
    #include "csapp.h"
}

using namespace std;

uint32_t SECRET_KEY;

void error(const char *msg)
{
    perror(msg);
    exit(1);
}

// Printing a separator
void printSep() {
    printf("%s\n", "-----------------------------");
}

typedef struct request_struct {
    uint32_t secret;
    uint32_t type;
    char filename[80];
    uint32_t size;
    int fileCt;
    int status;
    char filedata[100000];
} request;

// ./mycloudserver <TCP port> <secret key>
int main(int argc, char* argv[]) {
    int listenfd, connfd;
    socklen_t clientlen;
    struct sockaddr_storage clientaddr;
    char client_hostname[MAXLINE], client_port[MAXLINE];

    if (argc != 3) {
        printf("%s\n", "usage: ./mycloudserver <TCP port> <secret key>");
        exit(0);
    }

    printSep();
    printf("%s\n", "Welcome to the myCloud server.");
    printf("%s\n", "Attempting to listen for connections...");

    SECRET_KEY = atoi(argv[2]);

    listenfd = Open_listenfd(atoi(argv[1]));

    clientlen = sizeof(struct sockaddr_storage);
    connfd = Accept(listenfd, (SA *)&clientaddr, &clientlen);
    getnameinfo((SA *) &clientaddr, clientlen, client_hostname, MAXLINE,
                client_port, MAXLINE, 0);
    printSep();
    
    printf("Got connection from client (%s) on client port (%s).\n", client_hostname, client_port);
    printf("%s\n", "Client operations will be displayed below.");
    printSep();

    while (1) {

        request_struct requ;

        /* reading the type sent from the client */
        Rio_readn(connfd, &requ.type, 4);
        int code = ntohl(requ.type); 
                
        switch (code) {
            
            /* PUT */
            case 1:
            {
                printf("%s\n", "OPERATION: PUT");
                Rio_readn(connfd, &requ.secret, 4);
                uint32_t cliKey = ntohl(requ.secret);
                printf("KEY: %i\n", cliKey);

                request_struct requ;
                
                /* checking key, exit if incorrect */
                if (cliKey != SECRET_KEY) {
                    printf("%s\n", "STATUS: FAILURE");
                    
                    /* send failure response, 4 bytes */
                    requ.status = htonl(-1);
                    Rio_writen(connfd, &requ.status, 4);
                    printSep();
                    continue; /* ready for new request */
                }

                /* send success */
                requ.status = htonl(0);
                Rio_writen(connfd, &requ.status, 4);

                /* get file name */
                Rio_readn(connfd, &requ.filename, 80);
                printf("FILENAME: %s\n", requ.filename);

                /* get file size */
                Rio_readn(connfd, &requ.size, 4);
                uint32_t fileSize = ntohl(requ.size);
                printf("FILE SIZE: %u bytes\n", fileSize);

                /* get file data */
                if (fileSize <= 100000) {
                    Rio_readn(connfd, &requ.filedata, 92 + fileSize);
                    FILE* receivedFileData = fopen (requ.filename, "wb");  
                    fwrite (requ.filedata , sizeof(char), fileSize, receivedFileData);
                    printf("%s\n", "STATUS: SUCCESS");
                    requ.status = htonl(0);
                    Rio_writen(connfd, &requ.status, 4);
                    fclose (receivedFileData);                 
                } else {
                    printf("%s\n", "The file the client requested to send was too big.");
                }

                printSep();
                break;
            }
            case 2:
            {
                printf("%s\n", "OPERATION: GET");
                /* reading key */
                Rio_readn(connfd, &requ.secret, 4);
                uint32_t cliKeyHBO = ntohl(requ.secret);
                printf("KEY: %i\n", cliKeyHBO);

                if (cliKeyHBO != SECRET_KEY) {
                    requ.status = htonl(-1);
                } else {
                    requ.status = htonl(0);
                }

                /* send status */
                Rio_writen(connfd, &requ.status, 4);

                if (ntohl(requ.status) != 0) {
                    printf("%s\n", "STATUS: FAILURE");
                    printSep();
                    continue;
                }

                /* reading input file name */
                Rio_readn(connfd, &requ.filename, 80);
                printf("FILENAME: %s\n", requ.filename);

                /* checking if file exists */
                FILE* fileToSend;
                fileToSend = fopen(requ.filename, "rb");

                if (fileToSend == NULL) { 
                    printf("%s\n", "STATUS: FAILURE");
                    requ.status = htonl(-1);
                } else {
                    requ.status = htonl(0);
                }

                /* sending status (fail/success) */
                Rio_writen(connfd, &requ.status, 4);

                /* file exists, do operation... */
                if (ntohl(requ.status) == 0) {

                    /* getting size */
                    struct stat fileStat;
                    if (stat(requ.filename, &fileStat) != 0) {
                        printf("%s\n", "STATUS: FAILURE");
                    } else {
                        /* sending size */
                        uint32_t fileSize = uint32_t(fileStat.st_size);
                        printf("FILE SIZE: %i bytes\n", fileSize);
                        requ.size = htonl(fileSize);
                        Rio_writen(connfd, &requ.size, 4);

                        if (ntohl(requ.size) <= 100000) {
                            /* sending data */
                            fread(requ.filedata, 100000, 7 + (fileSize), fileToSend); /* putting file's data into char buffer */
                            Rio_writen(connfd, &requ.filedata, 7 + (fileSize)); 
                            printf("%s\n", "STATUS: SUCCESS");
                        } else {
                            printf("%s\n", "The file the client requested to retrieve was too big.");
                        }
                       
                    }
                }
                printSep();
                break;
            }

            case 3:
            {
                printf("%s\n", "OPERATION: DELETE");
            
                /* reading key */
                Rio_readn(connfd, &requ.secret, 4);
                uint32_t cliKeyHBO = ntohl(requ.secret);
                printf("KEY: %i\n", cliKeyHBO);

                if (cliKeyHBO != SECRET_KEY) {
                    requ.status = htonl(-1);
                } else {
                    requ.status = htonl(0);
                }

                /* send status */
                Rio_writen(connfd, &requ.status, 4);
                
                if (ntohl(requ.status) != 0) {
                    printf("%s\n", "STATUS: FAILURE");
                    printSep();
                    continue;
                }

                
                
                /* reading input file name */
                Rio_readn(connfd, &requ.filename, 80);
                printf("FILENAME: %s\n", requ.filename);

                /* sending success / fail back */
                if (remove(requ.filename) != 0) {
                    printf("%s\n", "STATUS: FAILURE");
                    requ.status = -1;
                } else {
                    printf("%s\n", "STATUS: SUCCESS");
                    requ.status = 0;
                }

                /* send status */
                requ.status = htonl(requ.status);
                Rio_writen(connfd, &requ.status, 4);

                printSep();

                break;
            }

            case 4:
            {
                printf("%s\n", "OPERATION: LIST");

                /* reading key */
                Rio_readn(connfd, &requ.secret, 4);

                uint32_t cliKeyHBO = ntohl(requ.secret);
                
                printf("KEY: %i\n", cliKeyHBO);

                if (cliKeyHBO != SECRET_KEY) {
                    requ.status = htonl(-1);
                } else {
                    requ.status = htonl(0);
                }

                Rio_writen(connfd, &requ.status, 4);

                if (ntohl(requ.status) != 0) {
                    printf("%s\n", "STATUS: FAILURE");
                    printSep();
                    continue;
                }

                printf("%s\n", "STATUS: SUCCESS");

                /* send number of files */
                requ.fileCt = 0;
                std::vector<string> fileNames;

                DIR *dir;
                struct dirent *ent;
                if ((dir = opendir (".")) != NULL) {
                  while ((ent = readdir (dir)) != NULL) {
                    //printf ("%s\n", ent->d_name);
                    fileNames.push_back(ent->d_name);
                    requ.fileCt++;
                    
                    
                  }
                  closedir (dir);
                } else {
                  /* could not open directory */
                    printf("%s\n", "Error, could not open directory.");
                }


                requ.fileCt = htonl(requ.fileCt);
                Rio_writen(connfd, &requ.fileCt, 4);

                /* send file names */
                for (uint32_t i = 0; i < ntohl(requ.fileCt); i++) {
                    //printf("%i\n", i);
                    memset(requ.filename, 0, 80);
                    strcpy(requ.filename, fileNames[i].c_str());
                    Rio_writen(connfd, &requ.filename, 80);
                }

                /* process key */
                printSep();
                break;
            }
        }
    }
}


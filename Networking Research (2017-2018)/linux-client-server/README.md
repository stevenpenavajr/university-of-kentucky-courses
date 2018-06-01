# Linux Client & Server Application
A simple client and server application to send and receive files less than 100KB.

### Date of Creation
November 2017

### Version
1.0

### Usage Instructions
After downloading the files as they are, in separate client/server directories:
1. Run ./mycloudserver TCPPort SecretKey in one directory (the key is an access code to connect the client)
2. Run ./mycloudclient ServerAddress TCPPort SecretKey (key must be the same)
3. Once connected, use any of these operations: cput <file> or cget <file> or cdelete <file> or clist

### Screenshot

![Alt text](screen.png?raw=true "Optional Title")

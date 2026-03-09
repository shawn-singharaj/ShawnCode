#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>

// Set up the address struct for the server socket
void setupAddressStruct(struct sockaddr_in* address, int portNumber){
  memset((char*) address, '\0', sizeof(*address)); 
  address->sin_family = AF_INET;
  address->sin_port = htons(portNumber);
  address->sin_addr.s_addr = INADDR_ANY;
}

// Receive exactly n bytes
int recvAll(int socket, char* buffer, int length) {
    int totalReceived = 0;
    int bytesReceived;
    
    while(totalReceived < length) {
        bytesReceived = recv(socket, buffer + totalReceived, length - totalReceived, 0);
        if(bytesReceived <= 0) {
            return -1;
        }
        totalReceived += bytesReceived;
    }
    return totalReceived;
}

// Send exactly n bytes
int sendAll(int socket, char* buffer, int length) {
    int totalSent = 0;
    int bytesSent;
    
    while(totalSent < length) {
        bytesSent = send(socket, buffer + totalSent, length - totalSent, 0);
        if(bytesSent <= 0) {
            return -1;
        }
        totalSent += bytesSent;
    }
    return totalSent;
}

int main(int argc, char *argv[]){
    int listenSocket, connectionSocket;
    struct sockaddr_in serverAddress, clientAddress;
    socklen_t sizeofClientInfo = sizeof(clientAddress);

    if (argc < 2) { 
        fprintf(stderr,"USAGE: %s port\n", argv[0]); 
        exit(1);
    } 

    // Create the socket that will listen for connections
    listenSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (listenSocket < 0) {
        perror("ENC SERVER: ERROR opening socket");
        exit(1);
    }

    // Allow socket reuse (MUST be after socket creation)
    int yes = 1;
    if(setsockopt(listenSocket, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) < 0) {
        perror("ENC SERVER: setsockopt failed");
    }

    // Set up address struct, takes 1 argument being port
    setupAddressStruct(&serverAddress, atoi(argv[1]));

    // Bind socket to port
    if(bind(listenSocket, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        perror("ENC SERVER: ERROR on binding");
        close(listenSocket);
        exit(1);
    }

    // Listen with backlog of 5
    if(listen(listenSocket, 5) < 0) {
        perror("ENC SERVER: ERROR on listen");
        close(listenSocket);
        exit(1);
    }

    // Handle zombie processes
    signal(SIGCHLD, SIG_IGN);

    // Accept connections
    while(1){
        connectionSocket = accept(listenSocket, (struct sockaddr *)&clientAddress, &sizeofClientInfo);
        if(connectionSocket < 0){
            perror("ENC SERVER: ERROR on accept");
            continue;
        }

        pid_t pid = fork();

        // child process
        if(pid == 0){
            close(listenSocket);

            char idBuffer[4];   
            memset(idBuffer, '\0', sizeof(idBuffer));
            int idRecv = recv(connectionSocket, idBuffer, 3, 0);
            if(idRecv < 0) {
                fprintf(stderr, "ENC SERVER: ERROR receiving client ID\n");
                close(connectionSocket);
                exit(1);
            }

            if (strcmp(idBuffer, "enc") != 0) {
                fprintf(stderr, "ENC SERVER: Invalid client\n");
                close(connectionSocket);
                exit(2);   
            }

            // Allocate text buffer
            char* textBuffer = malloc(100001);
            if(!textBuffer) {
                perror("ENC SERVER: malloc failed");
                close(connectionSocket);
                exit(1);
            }
            memset(textBuffer, '\0', 100001);

            // Receive plaintext (up to 100000 bytes)
            int textcharsRead = recvAll(connectionSocket, textBuffer, 100000);
            if(textcharsRead < 0){
                perror("ENC SERVER: ERROR reading plaintext from socket");
                free(textBuffer);
                close(connectionSocket);
                exit(1);
            }

            // Find actual length (look for null terminator)
            int actualLength = 0;
            for(int i = 0; i < 100000; i++) {
                if(textBuffer[i] == '\0') {
                    actualLength = i;
                    break;
                }
            }

            if(actualLength == 0) {
                fprintf(stderr, "ENC SERVER: Empty plaintext\n");
                free(textBuffer);
                close(connectionSocket);
                exit(1);
            }

            // Receive key (actualLength bytes)
            char *keyBuffer = malloc(actualLength + 1);
            if(!keyBuffer) {
                perror("ENC SERVER: malloc failed");
                free(textBuffer);
                close(connectionSocket);
                exit(1);
            }
            memset(keyBuffer, '\0', actualLength + 1);

            int keycharsRead = recvAll(connectionSocket, keyBuffer, actualLength);
            if(keycharsRead < 0){
                perror("ENC SERVER: ERROR reading key from socket");
                free(textBuffer);
                free(keyBuffer);
                close(connectionSocket);
                exit(1);
            }

            // Allocate output buffer
            char *buffer = malloc(actualLength + 1);
            if(!buffer) {
                perror("ENC SERVER: malloc failed");
                free(textBuffer);
                free(keyBuffer);
                close(connectionSocket);
                exit(1);
            }
            memset(buffer, '\0', actualLength + 1);

            // Encrypt using actualLength
            for(int i = 0; i < actualLength; i++){
                int textVal;
                if (textBuffer[i] == ' ') {
                    textVal = 26;
                } else {
                    textVal = textBuffer[i] - 'A';
                }

                int keyVal;
                if (keyBuffer[i] == ' '){
                    keyVal = 26;   
                }
                else{
                    keyVal = keyBuffer[i] - 'A'; 
                }
                int encryptChar = (textVal + keyVal) % 27;

                if(encryptChar == 26){
                    buffer[i] = ' ';
                }
                else{
                    buffer[i] = (char)(encryptChar + 'A');
                }
            }

            // Send encrypted text
            int sent = sendAll(connectionSocket, buffer, actualLength);
            if(sent < 0){
                perror("ENC SERVER: ERROR writing to socket");
            }

            free(textBuffer);
            free(keyBuffer);
            free(buffer);
            close(connectionSocket);
            exit(0);
        }
        // parent process listens
        else if(pid < 0){
            perror("ENC SERVER: ERROR forking");
            close(connectionSocket);
        }
        else{
            close(connectionSocket);
        }
    }

    close(listenSocket);
    return 0;
}
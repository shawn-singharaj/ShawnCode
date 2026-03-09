#include <stdio.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <ctype.h>

void setupAddressStruct(struct sockaddr_in* address, int portNumber){
  memset((char*) address, '\0', sizeof(*address)); 
  address->sin_family = AF_INET;
  address->sin_port = htons(portNumber);

  struct hostent* hostInfo = gethostbyname("localhost"); 
  if (hostInfo == NULL) { 
    fprintf(stderr, "ENC CLIENT: ERROR, no such host\n"); 
    exit(0); 
  }
  memcpy((char*) &address->sin_addr.s_addr, 
        hostInfo->h_addr_list[0],
        hostInfo->h_length);
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

int main(int argc, char *argv[]){
    int socketFD, textFD, textChars, keyFD, keyChars;
    struct sockaddr_in serverAddress;

    if(argc < 4){
        fprintf(stderr, "USAGE: %s plaintext key port\n", argv[0]);
        exit(1);
    }

    // Open plaintext file
    textFD = open(argv[1], O_RDONLY);
    if(textFD < 0){
        fprintf(stderr, "ENC CLIENT: ERROR opening plaintext file '%s'\n", argv[1]);
        exit(1);
    }

    // Allocate buffer for plaintext
    char* textBuffer = malloc(100001);
    if(!textBuffer) {
        fprintf(stderr, "ENC CLIENT: malloc failed\n");
        close(textFD);
        exit(1);
    }
    memset(textBuffer, '\0', 100001);

    textChars = read(textFD, textBuffer, 100000);
    close(textFD);

    if(textChars < 0) {
        fprintf(stderr, "ENC CLIENT: ERROR reading plaintext file\n");
        free(textBuffer);
        exit(1);
    }

    // Remove trailing newline
    if (textChars > 0 && textBuffer[textChars - 1] == '\n') {
        textBuffer[textChars - 1] = '\0';
        textChars--;   
    }
    textBuffer[textChars] = '\0';

    // Validate plaintext characters
    for(int i = 0; i < textChars; i++) {
        if(textBuffer[i] != ' ' && (textBuffer[i] < 'A' || textBuffer[i] > 'Z')) {
            fprintf(stderr, "ENC CLIENT: error: input contains bad characters\n");
            free(textBuffer);
            exit(1);
        }
    }

    // Open and read key file
    keyFD = open(argv[2], O_RDONLY);
    if(keyFD < 0){
        fprintf(stderr, "ENC CLIENT: ERROR opening key file '%s'\n", argv[2]);
        free(textBuffer);
        exit(1);
    }

    char *keyBuffer = malloc(textChars + 1);
    if(!keyBuffer) {
        fprintf(stderr, "ENC CLIENT: malloc failed\n");
        free(textBuffer);
        close(keyFD);
        exit(1);
    }
    memset(keyBuffer, '\0', textChars + 1);

    keyChars = read(keyFD, keyBuffer, textChars);
    close(keyFD);

    if(keyChars < textChars) {
        fprintf(stderr, "ENC CLIENT: Error: key '%s' is too short\n", argv[2]);
        free(textBuffer);
        free(keyBuffer);
        exit(1);
    }

    // Validate key characters
    for(int i = 0; i < textChars; i++) {
        if(keyBuffer[i] != ' ' && keyBuffer[i] != '\n' && (keyBuffer[i] < 'A' || keyBuffer[i] > 'Z')) {
            fprintf(stderr, "ENC CLIENT: error: key contains bad characters\n");
            free(textBuffer);
            free(keyBuffer);
            exit(1);
        }
    }
    keyBuffer[textChars] = '\0';

    // Create socket
    socketFD = socket(AF_INET, SOCK_STREAM, 0);
    if (socketFD < 0){
        perror("ENC CLIENT: ERROR opening socket"); 
        free(textBuffer);
        free(keyBuffer);
        exit(2);
    }

    setupAddressStruct(&serverAddress, atoi(argv[3]));

    // Connect to server
    if(connect(socketFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0){
        fprintf(stderr, "ENC CLIENT: Error: could not contact enc_server on port %s\n", argv[3]);
        free(textBuffer);
        free(keyBuffer);
        close(socketFD);
        exit(2);
    }

    // Send client ID
    char id[] = "enc";
    if(send(socketFD, id, strlen(id), 0) < 0) {
        perror("ENC CLIENT: ERROR sending ID");
        free(textBuffer);
        free(keyBuffer);
        close(socketFD);
        exit(2);
    }

    // Prepare buffer with null padding to 100000 bytes
    char* sendBuffer = malloc(100001);
    if(!sendBuffer) {
        fprintf(stderr, "ENC CLIENT: malloc failed\n");
        free(textBuffer);
        free(keyBuffer);
        close(socketFD);
        exit(2);
    }
    memset(sendBuffer, '\0', 100000);
    memcpy(sendBuffer, textBuffer, textChars);

    // Send plaintext (always 100000 bytes)
    if(sendAll(socketFD, sendBuffer, 100000) < 0){
        perror("ENC CLIENT: ERROR writing plaintext to socket");
        free(textBuffer);
        free(keyBuffer);
        free(sendBuffer);
        close(socketFD);
        exit(2);
    }
    free(sendBuffer);

    // Send key (exactly textChars bytes)
    if(sendAll(socketFD, keyBuffer, textChars) < 0){
        perror("ENC CLIENT: ERROR writing key to socket");
        free(textBuffer);
        free(keyBuffer);
        close(socketFD);
        exit(2);
    }

    // Receive ciphertext
    char* buffer = malloc(textChars + 1);
    if(!buffer) {
        fprintf(stderr, "ENC CLIENT: malloc failed\n");
        free(textBuffer);
        free(keyBuffer);
        close(socketFD);
        exit(2);
    }
    memset(buffer, '\0', textChars + 1);

    if(recvAll(socketFD, buffer, textChars) < 0){
        perror("ENC CLIENT: ERROR reading from socket");
        free(textBuffer);
        free(keyBuffer);
        free(buffer);
        close(socketFD);
        exit(2);
    }
    buffer[textChars] = '\0';

    printf("%s\n", buffer);

    close(socketFD); 
    free(textBuffer);
    free(keyBuffer);
    free(buffer);
    return 0;
}
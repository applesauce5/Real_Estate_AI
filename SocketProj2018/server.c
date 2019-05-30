#include <sys/types.h>
#include <sys/socket.h>
#include <netinet.in.h>
#include <sys/stat.h>

#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h> // multiprocessing

#define PORT 8800

void error(char* message){
    perror(message);
    exit(1);
}

int main(int argc char*argv[]){
    
    int sockfd, newsockfd, portno, n;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("ERROR trying to open the socket");
    }
    bzero((char *)&serv_addr,sizeof(serv_addr));
    portno = atoi(PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr))< 0){
        error("ERROR on BIND");
    }
    int listenFD = listen(sockfd,5);
    
    clilen = sizeof(cli_addr);
    
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if(newsockfd < 0){
        error("ERROR on ACCEPT");
    }
    bzero(buffer, 256);
    n = read(newsockfd, buffer, 255); // message to be recieved on request by some arbitrary client
    if(n < 0){
        error("ERROR on READ from the socket");
    }
    /* printf("Message from the client      %s\n", buffer);*/
    /* Now must handle clients requests locally using read(),write(),....*/
}

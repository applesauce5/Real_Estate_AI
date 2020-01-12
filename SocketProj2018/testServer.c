#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./RML/matrixops.h"

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){

    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    /* 
     * struct sockaddr_in {
     *      short sin_family; // AF_INET for internet
     *      u_short_port;
     *      struct in_addr sin_addr;
     *      char sin_zero[8];     
     * }
     *
     * struct in_addr {
     *      unsigned long s_addr
     * }
     */

    struct sockaddr_in serv_addr, cli_addr;
    int n;
    if (argc < 2){
        fprintf(stderr, "ERROR, no port provided\n");
        exit(1);
    }

    printf("CHECK 5\n");
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERROR trying to OPEN the socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = atoi(argv[1]);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
        error("ERROR on BIND");
    }

    printf("CHECK 3\n");

    int listenFD = listen(sockfd,5); 
    printf("LISTEN FD:  %i\n", listenFD);
    printf("CHECK 024\n");

    clilen = sizeof(cli_addr);
    
    printf("Checkpoint at --- newsockfd = accept(...)---\n");
    
    // opportunity to handle multiple requests from server code 
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
    printf("ACCEPT FD   %i\n",newsockfd);
    
    if(newsockfd < 0)
        error("ERROR on ACCEPT");
    
    printf("CHECK 2\n");

    bzero(buffer,256);

    printf("CHECK 1\n");
    n = read(newsockfd,buffer,255);
    if(n < 0)
        error("ERROR on READ from the socket");
    printf("Message given:    %s\n", buffer);
    printf("Testing RML part: \n");
    printf("Result testA .....\n");
    char* input[3] ={"","./RML/trainA.txt","./RML/testA.txt"} ;
    //char* train = "trainA.txt";
    //char* test = "testA.txt";
    //input[1]="trainA.txt";
    //input[2]="testA.txt";
    int args = 3;
    printf("%d\n",learn(args,input));
    n = write(newsockfd,"MESSAGE RECEIVED!!",18);
    if(n < 0)
        error("ERROR on WRITE through socket");
    return 0;
}

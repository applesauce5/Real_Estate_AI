#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "./RML/matrixops.h"

#define PORT 8080

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

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0)
        error("ERROR trying to OPEN the socket");
    
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = (PORT);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);

    if( bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0 ){
        error("ERROR on BIND");
    }

    int listenFD = listen(sockfd,5); 
    printf("LISTEN FD:  %i\n", listenFD);
    clilen = sizeof(cli_addr);
    
    printf("Currently listening to the open socket........\n");
    
    // opportunity to handle multiple requests from client 
    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    
    printf("accept() file descriptor  %i\n",newsockfd);
    
    if(newsockfd < 0)
        error("ERROR on ACCEPT");

    bzero(buffer,256); 

    while(!(strcmp(buffer,"exit\n\0") == 0)){ // comparison ----------------------
        // Reading message given from the client 
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);

        if(n < 0)
            error("ERROR on READ from the socket");
        printf("Message given:\n");
        printf("%s\n",buffer);
        
        if((strcmp(buffer,"testA\n") == 0)){ //The client is requesting testA
            printf("Testing RML part:..... \n");
            printf("Result testA .....\n");
        
            // List of sample inputs for the RML program
            char* input[3] ={"","./RML/trainA.txt","./RML/testA.txt"} ;
    
            int args = 3;
            printf("%d\n",learn(args,input)); //Requesting a call to linear regression part of the program
        }

        // Writing back to the client program
        if(strcmp(buffer,"exit\n\0")==0){
            n = write(newsockfd,"econf",5);
            if(n<0){
                error("ERROR on WRITE through socket");
            }
        } else {
            n = write(newsockfd,"MESSAGE RECEIVED!!",18);
            if(n < 0)
                error("ERROR on WRITE through socket");
        }
    }
    
    return 0;
}

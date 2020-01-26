//#include <stdio.h>
//#include <sys/types.h>
//#include <sys/socket.h>
//#include <netinet/in.h>
//#include <stdlib.h>
//#include <string.h>
//#include <unistd.h>
//#include <netdb.h>

#include "interface.h"

void error(char *msg){
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[]){
    int sockfd, portno, n;
    
    /* contains....
     * struct sockaddr_in {
     *      short sin_family;   // AF_INET for internet
     *      u_short sin_port;
     *      struct in_addr sin_addr;
     *      char sin_zero[8];
     * }
     *
     * struct in_addr {
     *      unsigned long s_addr;
     */
    struct sockaddr_in serv_addr;
    
    /* contains....
     * struct hostent {
     *      char *h_name;          // official name of host
     *      char **h_aliases;      // alias list
     *      int h_addrtype;        // host address type
     *      int h_length;          // length of address
     *      char **haddr_list[0]   // list of addresses from name server
     *  #define h_addr h_addr_list[0] // address, for backward compatibility
     */
    struct hostent *server;

    char buffer[256];
    if(argc < 2){
        fprintf(stderr,"usage %s hostname port\n",argv[0]);
        exit(0);
    }

    /* netserverinit() */

    portno = (PORT);
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("ERROR opening socket\n");
    }
    server = gethostbyname(argv[1]);
    if(server == NULL){
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);

    serv_addr.sin_port = htons(portno);

    // finished setup
    
    /* netopen(), netwrite(), netread() */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
        error(0);

    bzero(buffer,256);

    // interpret inputs here
    while(strcmp(buffer,"econf\0")!=0){ 
        printf("Please enter the message: \n");
        bzero(buffer,256);
        fgets(buffer, 255, stdin);

        printf("Line 80: write(...)\n");

        /* netwrite() */
        n = write(sockfd, buffer, strlen(buffer));
        if(n < 0){
            error("ERROR writing to socket");
        }
        bzero(buffer, 256);

        /* netread() */
        n = read(sockfd, buffer, 255);
        if(n < 0){
            error("ERROR reading from socket");
        }
        printf("%s\n", buffer);
    }
    return 0;
}





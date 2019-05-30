// #include <fcntl.h> // open() and posix calls
// #include <sys/stat.h> // files stuff
// #include <sys/socket.h> // socket stuff i.e. accept(), connect()...
// #include <netdb.h> // defines hostent struct
// #include <sys/types.h> // threads and mutex locks

#include "interface.h"

struct sockaddr_in serv_addr; // struct that holds fields that describe server
                              // i.e. IP address, PORT number  


/* returns 0 on success and -1 on error */
int netserverinit(char *hostname){ /* netserverinit(char *hostname,int filemode) ---for extention A */
    
    int sockfd;
    struct hostent *server;
    
    server = gethostbyname(hostname);
    if(server == NULL){
        fprintf(stderr,"ERROR, no such host\n");
        return -1;
    } 
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *) server->h_addr, (char *) &server_addr.sin_addr.s_addr, server->h_length);
    serv_addr.sin_port = htons(PORT);

    return 0;
}

/* returns a FD or -1 */
int netopen(const char *pathname, int flags){

    /* Initialize the socket */
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        error("ERROR opening socket\n");
        return -1;
    }
    
    /* Through the socket, make a connection using serv_addr */
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf("ERROR on CONNECT\n");
        return -1;
    }
    
    /* need to send meta data to the server.c */
    int writeFD;
    char *buffer; // meta data to be sent to the server
    buffer = malloc(sizeof(pathname) + 100);
    bzero(buffer,(int)sizeof(buffer));
    sprintf(buffer,"o %s %s", pathname, flags);

    writeFD = write(sockfd, buffer, strlen(buffer));

    free(buffer);
    
    /* return a file descriptor */
    return writeFD;
}

/* returns number of bytes read or -1 */
ssize_t netread(int fildes, void *buf, size_t nbyte){

    /* Open a socket */

    int sockfd, n, i;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd < 0){
        fprintf("ERROR on opening socket\n");
        return -1;
    }
    if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0){
        fprintf("ERROR on CONNECT\n");
        return -1;
    }
    if(nbyte == 0){
        fprintf("ERROR, requested to read 0 bytes");
        return -1;
    }

    /* Now need to perform read operations through the remote server */

    char buffer = malloc(sizeof(fildes) + sizeof(nbyte) + 100);
    bzero(buffer, sizeof(buffer));
    sprintf(buffer,"r %i %zu",fildes,nbyte);
    int bufferFD;
    bufferFD = write(sockfd, buffer, sizeof(buffer)); // sent
    if(bufferFD < 0){
        error("ERROR reading from socket"); 
        return -1;
    }

    /* Now needs to recieve 
    *  read() 
    * 
    *  Upon sending message to the server, the server will send
    *  a response that will contain the number of bytes read
    *  
    */

    //printf("MESSAGE READ:  %s\n", buffer);
    
    n = read(sockfd, buf, bufferFD);

    /* Now to read from buf, the number of bytes that have been read 
     *
     * buf = integer that represents the number of bytes read
     *
     */
    
    i = atoi(buf);
    
    return i; // placeholder...to be changed

}

/* returns number of bytes written or -1 */
ssize_t netwrite(int fildes, const void *buf, size_t nbyte){

}

/* returns 0 on success and -1 on error */
int netclose(int fd){

}



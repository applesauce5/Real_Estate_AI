

#ifndef _INTERFACE_FILES_H_
#define _INTERFACE_FILES_H_


// link major libraries between netFiles.c and the client
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>


#define PORT 8800

int netserverinit(char *, char *);
int netopen(const char *pathname, int flags);\
ssize_t netread(int fildes, void *buf, size_t nbyte);
ssize_t netwrite(int fildes, const void *buf, size_t nbyte);
int netclose(int fd);

#endif

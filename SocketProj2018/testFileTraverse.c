#include <stdlib.h>
#include <unistd.h>
#include <ftw.h>
#include <time.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>

int printDirectoryName(const char * fpath, const struct stat * buffer, int i){
    printf("filename: %s\n", fpath);
    printf("buffer");
    printf("typeflag: %d\n", i);
    return 0; // default
}

int main(){
    
    int ftwFD = ftw("../RML",printDirectoryName,FTW_D);
    printf("FD of ftwFD is : %d\n", ftwFD);
    return 0;
}

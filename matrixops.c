#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>


#include "matrixops.h"

extern int errno;

double* houseval;

double** insertMatrix(int rows, int cols, double **matrix, char* buffer, int q){
    int count1 = 0;
    int count2 = 0;
    int a = 0, b = 0;
    double num3;

    houseval = (double *)malloc(sizeof(double)*rows);

    char inputs[25];

    while(count1 < rows){
        matrix[count1] = (double *)malloc(cols * sizeof(double));
        while(count2 <= cols){
            a = 0;
            b = 0;
            while(buffer[q] != ',' && buffer[q] != '\n'){
                inputs[a] = buffer[q];
                a++;
                q++;
            }

            num3 = atof(inputs);
           
            if(count2 < cols){
                matrix[count1][count2] = num3;
            }
            if(count2 == cols){
                houseval[count1] = num3;
            }
            while(b<25){
                inputs[b] = 0.0;
                b++;
            }
            count2++;
            q++;
        }
        count2 = 0;
        count1++;
    }
   return matrix;    
}

double* getHouseval(){
    return houseval;
}

double** append(int rows,int cols,double** matrixb,double**matrixa){
    
    int i=0, j=0;

    while(i < rows){
    
        matrixb[i]=(double*) malloc(cols*sizeof(double));
        while(j < cols){
            if(j==0){
                matrixb[i][j]=1;
            }else{
                matrixb[i][j]=matrixa[i][j-1];
            }
            j++;
        }
        j=0;
        i++;
    }
    
    return matrixb;
}

char* extractFl(char* buffer ,const char* path){
   
    int fd = open(path,O_RDONLY);
    // int errnum;

    if(fd == -1){
        //errnum=errno;
        fprintf(stderr,"Value of errno: %d\n", errno);
        printf("Error opening file\n");
        //fprintf(stderr,"Error opening file: %s \n", strerror( errnum ));
        exit(0);
    }

    int byteRead=0, increase=0;

    do{
        if(byteRead==-1){
            fprintf(stderr,"Value of errno: %d\n", errno);
            printf("byteRead error on reading file");
            exit(0);
        }else{
            byteRead= read(fd,buffer+increase,5);
            printf("%s     \n",buffer);
            printf("======================\n");
        }
        increase+=5;
    }while(byteRead !=0);

    close(fd);

    return buffer; // file has been read into the buffer
}




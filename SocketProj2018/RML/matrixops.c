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

double** transpose(int rows,int cols,double** matrixb){

    int i=0,j=0;
    double** matrixc=(double**)malloc(sizeof(double*)*cols);

    while(i<cols){ 
        matrixc[i]=(double*)malloc(sizeof(double)*rows);
        while(j<rows){
            matrixc[i][j]=matrixb[j][i];
            j++;
        }
        j=0;
        i++;
    }
    return matrixc;
}


double** multiply(double** result,double**insert1,double**insert2,int rows, int cols){
    int i=0, j=0, k=0;
    while(i < cols){
        result[i]=(double*)malloc(sizeof(double)*cols);
        while(j < cols){
            result[i][j] = 0.0;
            while(k < rows){
                result[i][j]+=insert2[i][k]*insert1[k][j];
                k++;
            }
            k=0;
            j++;
        }
        j=0;
        i++;
    }
    return result;
}

double** appendIdentity(double** append,double** result,int cols, int appends){
    int i=0,j=0,k=0;
    while(i<cols){
        append[i]=(double*)malloc(sizeof(double)*(cols*2));
        while(j<appends){
            if(j<cols){
                append[i][j]=result[i][j];
            }
            if(j>=cols){
                append[i][j]=0;
            }
            if(j==appends-1){
                append[i][cols+k]=1;
            }
            j++;
        }
        k++;
        j=0;
        i++;
    }
    return append;
}

void gaussJordan(double** append, int cols,int appends){
    int i=0, j=0, jip=0,yt=0;
    double num9=0.0, key=0;

    while(i < cols){
        if(append[i][i] == 0){ // matrix not invertible
            printf("error10\n");
            exit(0);
        }
        if(append[i][i] != 1.0){ // column has potential pivot
            j=0;
            key = append[i][i];
            while(j < appends){
                if(append[i][j] != 0.0){
                    append[i][j]=(append[i][j]/key);
                }
                j++;
            }
        }

        // column has pivot
        // traverse column in order to product matrices -> identity matrix
        if((append[i][i]==1.0) || append[i][i]==(-1.0)){ 
            jip=0;
            if(append[i][i]==(-1.0)){ //convert pivot column
                yt=0;
                while(yt<appends){
                    append[i][yt]=(-1.0)*append[i][yt];
                    yt++;
                }
            }
        
            while(jip<cols){
            //if the row is not a pivot column
                if(i!=jip){
                    if(append[jip][i]<0){
                        yt=0;
                        num9=append[jip][i];
                        while(yt<appends){ // go through all columns
                            append[jip][yt]=append[jip][yt] - (num9 * append[i][yt]);
                            yt++;
                        }
                    }
                
                    if(append[jip][i]>0){
                        yt=0;
                        num9=append[jip][i];
                        while(yt<appends){
                            append[jip][yt]=append[jip][yt] - (num9 * append[i][yt]);
                            yt++;
                        }
                    }
                }
                jip++;
            }
        }
        i++;
    }
}

void converge(int cols ,double inverse[][cols],double** append){
    int i=0,j=0;
    while(i<cols){
        while(j<cols){
            inverse[i][j]=append[i][j+cols];
            j++;
        }
        j=0;
        i++;
    }

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




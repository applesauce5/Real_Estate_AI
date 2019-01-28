#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>

#include "matrixops.h"

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

#ifndef _INTERFACE_FILES_H_
#define _INTERFACE_FILES_H_


double* getHouseval();

double** insertMatrix(int rows, int cols, double **matrix, char* buffer, int q);

char* extractFl(char* buffer,const char* path);

double** append(int rows,int cols,double**matrixb,double**matrixa);

#endif 

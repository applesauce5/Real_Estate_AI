#ifndef _INTERFACE_FILES_H_
#define _INTERFACE_FILES_H_

int learn(int argc,char **argv);

double* getHouseval();

double** insertMatrix(int rows, int cols, double **matrix, char* buffer, int q);

char* extractFl(char* buffer,const char* path);

double** append(int rows,int cols,double**matrixb,double**matrixa);

double** transpose(int rows,int cols,double** matrixb);

double** multiply(double** result,double**insert1,double**insert2,int rows, int cols);

double** appendIdentity(double** append,double** result,int cols,int appends);
void gaussJordan(double**append,int cols,int appends);

void converge(int cols,double inverse[][cols],double** append);

#endif 

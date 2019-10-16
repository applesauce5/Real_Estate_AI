#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

#include "matrixops.h"

void printMatrix(double **matrix,int rows,int cols){
    int a = 0;
    int b = 0;
    while(a < rows){
        while(b < cols){
            printf("%f    ",matrix[a][b]);
        }
        printf("\n");
        a++;
        b = 0;
    }
}

static int q = 0; //reference to placement in buffer

int getNum(char*number,char*buffer,int size){
    
    int y = 0;
    bzero(number,sizeof(char)*size);

    while(buffer[q] != '\n'){
       number[y] = buffer[q];
       y++;
       q++;
    }
    ++q; // move past "new line" (\n) character
    return atoi(number);
}
int learn(int argc,char **argv){

	if(argc != 3){ // if there were ever more or less inputs
	    printf("1error\n");
	    return 0;
	} 

    int numByte=600000;

    char* buff = (char*) malloc(sizeof(char)*numByte);
    char* buff2 = (char*) malloc(sizeof(char)*numByte);
   
    bzero(buff,numByte);
    bzero(buff2,numByte);

    if(buff == NULL || buff2 == NULL){
        printf("8error \n");
        return 0;
    }

    /*
     * buffer contains train file
     * buffer2 contains test file
     *
     */

    char* buffer = extractFl(buff,argv[1]);
    char* buffer2 = extractFl(buff2,argv[2]);
	
	/* 
     * Begin to extract data about the matrices from the text files
     *
     * - needs to turn into a helper method maybe
     * - var q keeps track of reference point in buffer
     * 
     * */

    int size = 15;
    char* num1=(char*)malloc(sizeof(char*)*size);
    int attr = getNum(num1,buffer,size);
    free(num1);
	
    char* num2=(char*)malloc(sizeof(char*)*size);
    int train = getNum(num2,buffer,size);
    free(num2);

    
    /* matrix operations begin
     *
     * extract data from the buffer and enter information into data structures 
     *
     * */
    

    /* 
     *
     * Begin inserting into matrixa
     * Extract house values from the matrix 
     *
     * */

	double** matrixInsert = (double **)malloc(train * sizeof(double*));
    double** matrixa = insertMatrix(train,attr,matrixInsert,buffer,q);
    double* houseval = getHouseval();


    // prints out the results of the train and the house values
    int ui = 0;
    int ut = 0;
	while(ui<train){
	   while(ut<attr){
		printf("%f :)      ",matrixa[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
	
    free(buffer); // freeing memory space <!---------------------------->

	/*
     *
     * Append a column of value 1 to the matrix
     *  - new matrix will have additional column
     *
    */

    int rows = train;
    int cols = attr+1;
    double**appendMatrix=(double**)malloc(sizeof(double*)*rows);
    double** matrixb=append(rows,cols,appendMatrix,matrixa);

	/*
     *
     * Created an initialized the transpose of the matrix
     *
     */

    double**matrixc=transpose(rows,cols,matrixb);

    // <!--------------------------------------------------->

	//double result[cols][cols];
    double** initResult=(double**)malloc(sizeof(double*)*cols);
    double** result=multiply(initResult,matrixb,matrixc,rows,cols);

    /*
	* 
    * now to begin to calculate the inverse of the product
	*
    * first append an identity matrix of i^cols to results
    *
	*/
    
    int appends = 2*cols;
    double** insertAppend=(double**)malloc(sizeof(double*)*cols);
    double** append = appendIdentity(insertAppend,result,cols,appends);
    

	// now to perform gauss-jordan elimination
	int i = 0;

    gaussJordan(append,cols,appends);


	// now finished with gauss-jordan elimination

	// finish finding w
	// will convert the augmented matrix into one cohesive matrix
	
    
    double inverse[cols][cols];
    converge(cols,inverse,append);

    
	double result2[cols][rows];

	double num0,num4;
	i = 0;
	int id = 0;
	int yu = 0;
	while(i < rows){
  	   while(id < cols){
		result2[id][i] = 0.0;
		while(yu < cols){
		    num0 = inverse[id][yu];
		    num4 = matrixc[yu][i];
		    result2[id][i] =result2[id][i] + (num0 * num4);
		    yu++;
        }
        yu = 0;
        id++;
       }
	id = 0;
	i++;
	}
	// prints the product of X^-1 and X^T
	// Column Y is housVal[] column 

	double weight[rows];  // vertical vector
	ui=0;
	yu = 0;

	while(ui<cols){
		weight[ui] = 0;
		while(yu<rows){
		    weight[ui] += (result2[ui][yu] * houseval[yu]);
		yu++;
		}
	yu = 0;
	ui++;
	}

	//final step!!! begin dissecting buffer2
	int y;
	q = 0;
	y = 0;
	char numRow[20];
    /*
	while(y<20){
	   numRow[y] = '\0';
	   y++;
	}
    */
	y = 0;
	while(buffer2[q] != '\n'){ //now have a char array of the number
	   numRow[y] = buffer2[q];
	   y++;
	   q++;
	}
	q++; //move paset the new line
	int ele = atoi(numRow);

	double final[ele][cols-1];

/////////////////////
	double num34;

	char inputs2[25]; //for the inputs

    int insertNum = 0;
    int clearBuff = 0;
	int rowCt = 0;
	int colCt = 0;

	// put stuff into matrixa
	while(rowCt < ele){// move across rows

	   while(colCt < cols -1){//move across columns
	
            insertNum = 0;
            clearBuff = 0;
	        while(buffer2[q] != ',' && buffer2[q] != '\n'){//read number
	            inputs2[insertNum] = buffer2[q];
		        insertNum++;
		        q++;
  	        }
	        num34 = atof(inputs2); // char number has been converted to a double
		    final[rowCt][colCt] = num34;
	      	      
	        while(clearBuff<25){
	            inputs2[clearBuff] = 0.0;
	            clearBuff++;
	        }
	        colCt++;
  	        q++;
	   }
       colCt = 0;
       rowCt++;
    }

	double final1[ele][cols];

////////////////////

	y = 0;
	q = 0;

	while(y<ele){
		while(q<cols){
		
		if(q == 0){
			final1[y][q] = 1;
		}
		else{
			final1[y][q] = final[y][q-1];
		}		
		q++;
		}
	q=0;
	y++;
	}
/*	q=0;
	y=0;
	while(q<ele){
		while(y<cols){
		printf("%f    ",final1[q][y]);
		y++;
		}
	printf("\n");
	y=0;
	q++;
	}
*/
	ui = 0;
	yu = 0;
	double Y[ele];
	double finalNum;
	while(ui<ele){
		finalNum = 0;
		while(yu<cols){
		   finalNum += (final1[ui][yu] * weight[yu]);
		yu++;
		}
	Y[ui] = finalNum;
	yu = 0;
	ui++;
	}
	
	ui = 0;	
	while(ui<ele){
		printf("%0.0f\n",Y[ui]);
	ui++;
	}
	free(buffer2); // free test.txt buffer
    return 0;

}
/**
int main(int argc, char **argv){
    int l= learn(argc, argv);
    printf("Status of program: %d\n",l);
    return 0;
}
**/


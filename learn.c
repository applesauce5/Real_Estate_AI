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

int main(int argc,char **argv){

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

     

    int i=0,id=0;
    ui=0;
	//	transpose(rows,cols,matrixb);


	// find the transpose double matrixc[cols][rows]; // to be transpose of matrix b

	double matrixc[cols][rows];
	i = 0;
	id = 0;

	while(i<cols){
	   while(id<rows){
		matrixc[i][id] = matrixb[id][i];
	        id++;
	   }
	id = 0;
	i++;
	}

       	// prints out the transpose of matrixb, matrixc
/*	printf("-------------tttttt--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<rows){
		printf("%f  ",matrixc[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/
	i = 0;
	id = 0;
	int yu = 0;

	double result[cols][cols];

/*	while(id < cols){
	   while(i<cols){
	   result[i][id] = '\0';
	   i++;
	   }
	i = 0;
	id++;
	}*/
	i = 0;
	id = 0;
// printf("element1   : %f\n",matrixc[0][0]);/////////////////////////////

    /* transpose of matrix b times matrix b  */
	while(i < cols){ 
	   while(id < cols){//-1){
		result[i][id] = 0.0;
		while(yu < rows){
	        // printf("c[0][0] is %f i%d|id%d|yu%d\n", matrixc[0][0], i, id, yu);
			result[i][id] += matrixc[i][yu]*matrixb[yu][id];
			yu++;
		}
		
	   yu = 0;
	   id++;
	   }
	id = 0;
	i++;
	}
// printf("element2   : %f\n",matrixc[0][0]);/////////////////////////////
/*	printf("-------------ccccc22222--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<rows){
		printf("%f  ",matrixc[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/
	i = 0;
	id = 0;
	yu = 0;
/*
	//this is the product of x^t and x
	printf("-------------000--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<cols){
		printf("%f  ",result[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/

	// now to begin to calculate the inverse of the product
	//
	//
	//
	
	// first append an identity matrix of i^cols to results
	int appends = 2*cols;	

	double append[cols][appends];

	int counta = 0;

	int h = 0;
	int l = 0;
	while(h<cols){
	   while(l<appends){
	   
	   if(l < cols){
	   append[h][l] = result[h][l];
	   }

	   if(l >= cols){		
	   append[h][l] = 0;
	   }
	   if(l == appends - 1){
		append[h][cols+counta] = 1;
	   }
	   l++;
	   }
	counta++;
	l=0;
	h++;
	}
	//identity matrix augmented to the product matrix
 /*
	printf("-------------000--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<appends){
		printf("%f  ",append[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/

	// now to perform gauss-jordan elimination
	i = 0;
	int j = 0;
	int jip = 0;
	int yt = 0;
	double num9 = 0.0;
	double key = 0;

	while(i < cols){
	   if(append[i][i] == 0){ // this matrix is not invertible
		printf("error10\n");
		return 0;
	   }
	   if(append[i][i] != 1.0){ // this column has potential pivot
		j=0;
		key = append[i][i];
	   	while(j<appends){
		   if(append[i][j] != 0.0){
		   append[i][j] = (append[i][j]/key);
		   }
		   j++;
		}
	   }
	   
	   if((append[i][i] == 1.0) || append[i][i] == (-1.0)){ // this column is a pivot
             //want to traverse column to turn the product matrices into an identity matrix
	    
	      jip = 0; // initializes count to 0
	      
	      if(append[i][i] == (-1.0)){ // convert the pivot column
		yt = 0;
		while(yt < appends){
		   append[i][yt] = (-1.0)* append[i][yt];
		yt++;
		}
	      }
	      while(jip < cols){	
		if(i != jip){ // only if the row is not a pivot column
		   if(append[jip][i] < 0){

			yt = 0;
			num9 = append[jip][i]; //some number

			while(yt < appends){ // go through all columns
			   append[jip][yt] = append[jip][yt] - (num9 * append[i][yt]);
			   yt++;
			} 
		   }
		   if(append[jip][i] > 0){
			yt = 0;
			num9 = append[jip][i];
			
			while(yt < appends){ // go through all columns
			   append[jip][yt] = append[jip][yt] - (num9 * append[i][yt]);
			   yt++;
			} 
		   }
		}	
 	      jip++;   
	      }
	   }
	i++;
	}
/*
	printf("-------------ii--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<appends){
		printf("%f  ",append[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/

	// now finished with gauss-jordan elimination

	// finish finding w
	// will convert the augmented matrix into one cohesive matrix
	double inverse[cols][cols];
	i = 0;
	j = 0;
	while(i < cols){
	   while(j < cols){
	    inverse[i][j] = append[i][j+cols];
	   j++;
	   }
	j = 0;
	i++;
	}
/*
	printf("-------------iiii--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<cols){
		printf("%f  ",inverse[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/
/*	printf("-------------ccccc22222--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<rows){
		printf("%f  ",matrixc[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/
	double result2[cols][rows];
/*	while(id < rows){
	   while(i<cols){
	   result[i][id] = '\0';
	   i++;
	   }
	i = 0;
	id++;
	}
*/
	double num0,num4;
	i = 0;
	id = 0;
	yu = 0;
	while(i < rows){
  	   while(id < cols){
		result2[id][i] = 0.0;
		while(yu < cols){
//printf("multiplying ......I: %f   C:%f \n",inverse[id][yu],matrixc[yu][i]);
		num0 = inverse[id][yu];
		num4 = matrixc[yu][i];
		result2[id][i] =result2[id][i] + (num0 * num4);
		yu++;
		}
//		printf("result at col   %f\n",result2[id][i]);
	   yu = 0;
	   id++;
	   }
	id = 0;
	i++;
	}
	// prints the product of X^-1 and X^T
/*	printf("-------------WWWWW1/2--------------\n");
	ui = 0;
	ut = 0;
	while(ui<cols){
	   while(ut<rows){
		printf("%f  ",result2[ui][ut]);
		ut++;
	   }
	printf("\n");
	ui++;
	ut = 0;
	}
*/	
	// Column Y is housVal[] column 
/*
	printf("---------------YYYYYYYYY------------------------\n");
	ui = 0;
	while(ui<train){
	printf("%f\n",houseval[ui]);
	ui++;
	}
*/	
	double weight[rows];  // vertical vector
	ui=0;
	//ut= 0;
	yu = 0;

	while(ui<cols){
		weight[ui] = 0;
		while(yu<rows){
//		printf("Multiplying.... R:   %f   H   %f\n",result2[ui][yu], houseval[yu]);
		    weight[ui] += (result2[ui][yu] * houseval[yu]);
//			printf("the product!!:     %f\n",weight[ui]);
	
		yu++;
		}
//	printf("the product------:     %f\n",weight[ui]);
	yu = 0;
	ui++;
	}
/*	
	yu = 0;
	while(yu < cols){
	    printf("%f\n",weight[yu]);
	yu++;
	}
*/
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


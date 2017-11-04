#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	int *matrix;
	if(argc < 3){
		printf("Wrong Input\nShould be ./randMatrix r c\n");
	}
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);
	int size = row*col;
	matrix = malloc(size*sizeof(int));
	int i = 0;

	srand(time(NULL));
	for(i = 0; i < size; i++){
		matrix[i] = rand() % 2;
	}

	//print out matrix to file crtMatrix.txt
	FILE *fileOut;
	fileOut = fopen("crtMatrix.txt","w");
	int j =0;
	for(i=0; i< col; i++){
		for(j=0; j < row; j++){
			fprintf(fileOut, "%d", matrix[i*row + j]);
			//fprintf(fileOut, "\t");
			fprintf(fileOut,"\n");
		}
		//fprintf(fileOut,"\n");
	}

	fclose(fileOut);


}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <omp.h>


int main(int argc, char *argv[])
{
	FILE * fileIn;
	fileIn = fopen("crtMatrix.txt","r");
	FILE * outFile;
	outFile = fopen("movingMatrix.txt","w");

	int *m;
	if(argc < 3){
		printf("Wrong input, should be: ./mvMatrix r c mov\n");
		return 1;
	}
	int row = atoi(argv[1]);
	int col = atoi(argv[2]);
	int mov = atoi(argv[3]);
	int size = row*col;
	m = (int*)malloc(size*sizeof(int));
	int i = 0;

	for(i = 0; i < size; i++){
		fscanf(fileIn, "%d", &m[i]);
	}
	fclose(fileIn);

	srand(time(NULL));
	int j = 0, k = 0;
	for(k = 0; k < mov; k++){
		for(i = 0; i < col; i++){
			for(j = 0; j < row; j++){
				if(m[i*row + j] == 1){
					switch(rand()%9){
						case 0 : //northwest
							if((i==0) || (j==0)){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[(i-1)*row + (j-1)] = 1;
							}
							break;
						case 1 : //north
							if(i==0){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[(i-1)*row + j] = 1;
							}
							break;
						case 2 : //northeast
							if((i==0) || (j==(row-1))){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[(i-1)*row + (j+1)] = 1;
							}
							break;
						case 3 : //west
							if(j==0){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[i*row + (j-1)] = 1;
							}
							break;
						case 4 : //center
							m[i*row + j] = 1;
							break;
						case 5 : //east
							if(j==(row-1)){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[i*row + (j+1)] = 1;
							}
							break;
						case 6 : //southwest
							if((i==(col-1)) || (j==0)){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[(i+1)*row + (j-1)] = 1;
							}
							break;
						case 7 : //south
							if(i==(col-1)){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[(i+1)*row + j] = 1;
							}
							break;
						case 8 : //southeast
							if(i==(col-1) || j==(row-1) ){
								m[i*row + j] = 0;
							}
							else {
								m[i*row + j] = 0;
								m[(i+1)*row + j+1] = 1;
							}
							break;
						default:
							m[i*row + j] = 1;
					}
				}
			}
		}
		for(i=0; i< col; i++){
			for(j=0; j < row; j++){
				fprintf(outFile, "%d", m[i*row + j]);
				//fprintf(outFile, "\t");
				fprintf(outFile,"\n");
			}
			//fprintf(outFile,"\n");
		}	
	}

	fclose(outFile);
	free(m);




}
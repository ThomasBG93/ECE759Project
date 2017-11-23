#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <omp.h>
#include "creature_char.h"

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Wrong input, should be: ./move len numCreatures\n");
		return 1;
	}
	int size = atoi(argv[2]); //numCreatures;
	int len = atoi(argv[1]);	//length of one side
	int i = 0;
	FILE* fp;
	creature *array = (creature *)malloc(size * sizeof(creature));
	fp = fopen("input.txt", "r");
	for(int i = 0; i < size; i++) {
		fscanf(fp, "%d\n", &array[i].id);
		fscanf(fp, "%lf\n", &array[i].strength);
		fscanf(fp, "%d\n", &array[i].lifetime);
		fscanf(fp, "%d\n", &array[i].fertility);
		fscanf(fp, "%d\n", &array[i].aliveOrDead);
		fscanf(fp, "%d\n", &array[i].isPaired);
		fscanf(fp, "%d\n", &array[i].xPos);
		fscanf(fp, "%d\n", &array[i].yPos);
	}
	fclose(fp);
	srand(time(NULL));
	int xchange = 0;
	int ychange = 0;
	for(i=0; i < size; i++){
		xchange = (rand()%3) -1;
		ychange = (rand()%3) -1;
		//printf("Before[%d]: (%d,%d)\n",i,array[i].xPos,array[i].yPos);
		//TODO do we want to wrap or fall off?
		array[i].xPos = array[i].xPos + xchange;
		if(array[i].xPos >= len){
			array[i].xPos = 0;
		}
		if(array[i].xPos < 0){
			array[i].xPos = len - 1;
		}
		array[i].yPos = array[i].yPos + ychange;
		if(array[i].yPos >= len){
			array[i].yPos = 0;
		}
		if(array[i].yPos < 0){
			array[i].yPos = len - 1;
		}
		//printf("After[%d]: (%d,%d)\n",i,array[i].xPos,array[i].yPos);
	}

	fp = fopen("testMove.txt", "w");
	for(int i =0; i < size; i++){
		fprintf(fp, "%d\n", array[i].id);
		fprintf(fp, "%f\n", array[i].strength);
		fprintf(fp, "%d\n", array[i].lifetime);
		fprintf(fp, "%d\n", array[i].fertility);
		fprintf(fp, "%d\n", array[i].aliveOrDead);
		fprintf(fp, "%d\n", array[i].isPaired);
		fprintf(fp, "%d\n", array[i].xPos);
		fprintf(fp, "%d\n", array[i].yPos);
	}
	fclose(fp);


	free(array);
	return 0;

}
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "creature_char.h"


void move(int i, int len, creature *array);

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Wrong input, should be: ./move length numCreatures numThreads\n");
		return 1;
	}
	int size = atoi(argv[2]); //numCreatures;
	int len = atoi(argv[1]);	//length of one side
	int numThreads = atoi(argv[3]);
	//TODO should numThreads be set globally?
	omp_set_num_threads(numThreads);
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
	double start, end, time;
	start = omp_get_wtime();
	#pragma omp parallel for
		for(i=0; i < size; i++){
			//printf("Before[%d]: (%d,%d)\n",i,array[i].xPos,array[i].yPos);
			//move(i,len,array);
				int xchange = (rand()%3) -1;
				int ychange = (rand()%3) -1;
				//usleep(100);
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

	end = omp_get_wtime();
	time = (end-start)*1000;
	printf("Time: %f\n",time);
	

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

void move(int i, int len, creature *array)
{
	int xchange = (rand()%3) -1;
	int ychange = (rand()%3) -1;
	//usleep(100);
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
	
}
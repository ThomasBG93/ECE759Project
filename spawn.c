#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
//#include <omp.h>
#include "creature_char.h"


void spawn(creature *array, int size, int len);

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Wrong input, should be: ./spawn length numCreatures numThreads\n");
		return 1;
	}
	int size = atoi(argv[2]); //numCreatures;
	int len = atoi(argv[1]);	//length of one side
	int numThreads = atoi(argv[3]);
	//TODO should numThreads be set globally?

	FILE* fp;
	creature *array = (creature *)malloc(size * sizeof(creature));
	fp = fopen("input.txt", "r");
	for(int i = 0; i < size; i++) {
		fscanf(fp, "%d\n", &array[i].id);
		fscanf(fp, "%lf\n", &array[i].strength);
		fscanf(fp, "%d\n", &array[i].lifetime);
		fscanf(fp, "%d\n", &array[i].base_life);
		fscanf(fp, "%d\n", &array[i].fertility);
		fscanf(fp, "%d\n", &array[i].aliveOrDead);
		fscanf(fp, "%d\n", &array[i].isPaired);
		fscanf(fp, "%d\n", &array[i].xPos);
		fscanf(fp, "%d\n", &array[i].yPos);
		fscanf(fp, "%d\n", &array[i].killedBy);
	}
	fclose(fp);
	srand(time(NULL));

	//double start, end, time;
	// try for 25 iters
	for(int i = 0; i < 24; i++)
		spawn(array, size, len);

	
	// start = omp_get_wtime();
	// #pragma omp parallel for
	/*#pragma omp parallel
	{
		#pragma omp single
		start = omp_get_wtime();

		
		move(array,size,len);

		#pragma omp barrier
		#pragma omp single
		end = omp_get_wtime();
	}*/

	// end = omp_get_wtime();
	//time = (end-start)*1000;
	//printf("Time: %f\n",time);
	

	fp = fopen("out_spawn.txt", "w");
	for(int i =0; i < size; i++){
		fprintf(fp, "%d\n", array[i].id);
		fprintf(fp, "%f\n", array[i].strength);
		fprintf(fp, "%d\n", array[i].lifetime);
		fprintf(fp, "%d\n", array[i].base_life);
		fprintf(fp, "%d\n", array[i].fertility);
		fprintf(fp, "%d\n", array[i].aliveOrDead);
		fprintf(fp, "%d\n", array[i].isPaired);
		fprintf(fp, "%d\n", array[i].xPos);
		fprintf(fp, "%d\n", array[i].yPos);
		fprintf(fp, "%d\n", array[i].killedBy);
	}
	fclose(fp);


	free(array);
	return 0;

}
// len is the size of one dimension of the board and size is how big array is
void spawn( creature *array, int size, int len)
{
	//unsigned int seed;
	int i = 0;
	for(i=0; i < size; i++){
		//printf("Before[%d]: (%d,%d)\n",i,array[i].xPos,array[i].yPos);
		//usleep(100);
		//TODO do we want to wrap or fall off?
		if(array[i].aliveOrDead == 1 && (array[i].lifetime % array[i].fertility == 0))
		{
			for(int j = 0; j < size; j++)
			{
				if(array[j].aliveOrDead == 0)
				{
					// retain creature id
					array[j].id = array[i].id;
					array[j].strength = array[i].strength + (rand()%7) - 3;
					 
					array[j].base_life = array[i].base_life + (rand()%11) - 5;
					array[j].lifetime = array[j].base_life;
					array[j].aliveOrDead = 1;
					array[j].isPaired = -1;
					int xchange = (rand()%11) - 5;
					int ychange = (rand()%11) - 5;
					array[j].xPos = array[j].xPos + xchange;
					if(array[j].xPos >= len){
						array[j].xPos = 0;
					}
					if(array[j].xPos < 0){
						array[j].xPos = len - 1;
					}
					array[j].yPos = array[j].yPos + ychange;
					if(array[j].yPos >= len){
						array[j].yPos = 0;
					}
					if(array[j].yPos < 0){
						array[j].yPos = len - 1;
					}
					array[j].killedBy = -1;
					// keep an upper and lower bound on strength
					if(array[j].strength > 10)
						array[j].strength = 10.0;
					else if(array[j].strength < 0)
						array[j].strength = 0.0;
					printf("creature %d spwaned creature %d\n",i,j);
					break;
				}
			}
			
		}
	}
	
}
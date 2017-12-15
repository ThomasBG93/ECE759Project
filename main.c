#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "creature_char.h"


void check_conflict(creature *array, int n);
void move( creature *array, int size, int len);
int resolve( creature* array, int size);
void spawn( creature *array, int size, int len, int iter);
void subAndCheckIfAlive(creature *array, int size);

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Wrong input, should be: ./main length numCreatures numThreads\n");
		return 1;
	}
	int size = atoi(argv[2]); //numCreatures;
	int len = atoi(argv[1]);	//length of one side
	int numThreads = atoi(argv[3]);

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
	for(int i = 0; i < 100000; i++)
	{
		check_conflict(array, size);
		resolve(array, size);
		move(array, size, len);
		check_conflict(array, size);
		resolve(array, size);
		spawn(array, size, len, i);
    subAndCheckIfAlive(array, size);
    //printf("iter num: %d\n", i); 
		//if(iter % 20)
		//	writeMatrix(array);
	}
	
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
	

	fp = fopen("main.txt", "w");
	for(int i =0; i < size; i++){
		fprintf(fp, "%d\n", array[i].id);
		fprintf(fp, "%lf\n", array[i].strength);
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

void check_conflict(creature *array, int n){
		FILE* san;
		san = fopen("sanityCheck.txt","w");
		for(int i = 0; i < n - 1; i++){
			if(array[i].isPaired == -1 && array[i].aliveOrDead == 1){
				for(int j = i + 1; j < n; j++){
					if(array[i].xPos == array[j].xPos && array[i].yPos == array[j].yPos && array[j].aliveOrDead == 1){
						array[i].isPaired = j;
						array[j].isPaired = i;
						fprintf(san,"isPaired: %d --> %d\n",i,j);
					}
				}
			}
		}
		fclose(san);

}
void move( creature *array, int size, int len)
{
	unsigned int seed;
	int i = 0;
	#pragma omp for
	for(i=0; i < size; i++){
		//printf("Before[%d]: (%d,%d)\n",i,array[i].xPos,array[i].yPos);
		seed = omp_get_thread_num();
		int xchange = (rand_r(&seed)%3) -1;
		int ychange = (rand_r(&seed)%3) -1;
		//usleep(100);
		//TODO do we want to wrap or fall off?
		if(array[i].lifetime <= 0){
			array[i].aliveOrDead = -1;
		}
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
	
}

int resolve( creature* array, int size)
{
	//FILE* san;
	//san = fopen("sanityResolve.txt","w");
	int i;
	int j =0;
	int killedOff = 0;
	for(i=0; i < size; i++){
		if(array[i].isPaired > -1){
			j = array[i].isPaired;
			//printf("%d:%d\n",i,j);
			//printf("%d killedBy %d\n",j,array[j].killedBy);
			if(array[j].isPaired == i){	//if paired with you then regular killing
				if(array[i].strength >= array[j].strength){
					array[j].aliveOrDead = 0;
					array[j].isPaired = -1;
					array[j].killedBy = i;

					array[i].isPaired = -1;
					array[i].lifetime += array[j].lifetime;
					killedOff += 1;
					//fprintf(san,"%d killed %d\n",i,j);
					printf("%d killed %d\n",i,j);
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;

					array[j].isPaired = -1;
					array[j].lifetime += array[i].lifetime;
					killedOff += 1;
					//fprintf(san,"%d killed %d\n",j,i);
					printf("%d killed %d\n",j,i);
				}
			}else{ //the creature you are paired with is not paired with you

				while(array[j].killedBy != -1){	//the creature you are paired with is already killed
					j = array[j].killedBy;		// pair yourself with the creature that killed the creature you were paired with
				}
				if(array[i].strength >= array[j].strength){
					array[j].aliveOrDead = 0;
					array[j].isPaired = -1;
					array[j].killedBy = i;

					array[i].isPaired = -1;
					array[i].lifetime += array[j].lifetime;
					killedOff += 1;
					//fprintf(san,"%d killed %d\n",i,j);
					printf("%d killed %d\n",i,j);
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;

					array[j].isPaired = -1;
					array[j].lifetime += array[i].lifetime;
					killedOff += 1;
					//fprintf(san,"%d killed %d\n",j,i);
					printf("%d killed %d\n",j,i);
				}
			}
			
			
		}
	}
	//fclose(san);
	return killedOff;
}
void spawn( creature *array, int size, int len, int iter)
{
	//unsigned int seed;
	int i = 0;
	for(i=0; i < size; i++){
		//printf("Before[%d]: (%d,%d)\n",i,array[i].xPos,array[i].yPos);
		//usleep(100);
		//TODO do we want to wrap or fall off?
		if(array[i].aliveOrDead == 1 && (iter % array[i].fertility == 0))
		{
			for(int j = 0; j < size; j++)
			{
				if(array[j].aliveOrDead == 0)
				{
					// retain creature id
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
					printf("creature %d spawned creature %d\n",i,j);
					break;
				}
			}
			
		}
	}
}
void subAndCheckIfAlive(creature *array, int size)
{
    // check if alive or dead is set and then check lifetime==1
    // if so set to dead
    // else sub by 1
    for(int i = 0; i < size; i++)
    {
        if(array[i].aliveOrDead == 1)
        {
              if(array[i].lifetime==1){
                  array[i].lifetime = 0;
                  array[i].aliveOrDead = 0;
                  printf("creature %d has died!\n", i);
              }
              else{
                  array[i].lifetime--;
              }
        }
    }
}

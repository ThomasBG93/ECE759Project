#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <assert.h>
#include <errno.h>
#include <omp.h>
#include "creature_char.h"

#define STEPAMOUNT 1000

void check_conflict(creature *array, int n);
void move( creature *array, int size, int len);
int resolve( creature* array, int size);
void spawn( creature *array, int size, int len, int iter);
void subAndCheckIfAlive(creature *array, int size);
void printMatrix(creature *array, int size, int len, void* base_img, int* aliveList);

void printMatrix(creature *array, int size, int len, void* base_img, int* aliveList)
{
	int *data; 

	int *data_base = (int *) base_img;

	for(int i = 0; i < size; i++)
	{
		aliveList[i] = 0;
	}
	for(int i =0; i < size; i++){

		int index = array[i].xPos + (array[i].yPos)*len;

		if(array[i].aliveOrDead)
		{
			aliveList[index] = array[i].strength;
		}

	}
	data = data_base;
	for(int i =0; i < size; i++)
	{
		data[i] = aliveList[i];
	}


}

int main(int argc, char *argv[])
{
	if(argc < 2){
		printf("Wrong input, should be: ./main numThreads\n");
		return 1;
	}



	int len = 100;	//length of one side
	int numThreads = atoi(argv[1]);
	int size = len*len;

	omp_set_num_threads(numThreads);

	srand(time(NULL));
	creature *array = (creature *)malloc(size * sizeof(creature));
	for(int i = 0; i < size ; i++){
		array[i].id = i;
		array[i].strength = rand() % 32 + 1;
		array[i].lifetime = rand() % 5 + 35;
		array[i].base_life = array[i].lifetime;
		array[i].fertility = rand() % 20 + 45;
		array[i].xPos = rand() % len; 
		array[i].yPos = rand() % len;
		array[i].isPaired = -1;
		array[i].killedBy = -1;
		//made minor change here
		if(i < size/20)
			array[i].aliveOrDead = 1;
		else 
			array[i].aliveOrDead = 0;
	}

	int *aliveList = (int*)malloc(size*sizeof(int));
	int fd = open("movingMatrix.txt", O_RDWR );
	void *base_img = mmap(NULL, 4*size,PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
	if(base_img == MAP_FAILED)
		fprintf(stdout,"errno: %i\n",errno);

	double start, end, time, count;
	count = 0;
	#pragma omp parallel
	{

		#pragma omp single
		start = omp_get_wtime();
		for(int i = 0; i < STEPAMOUNT; i++)
		{
	
			#pragma omp single
			check_conflict(array, size);

			#pragma omp single
			resolve(array, size);

			#pragma omp single
			printMatrix(array,size, len, base_img, aliveList);


			move(array, size, len);
		
			

			#pragma omp single
			check_conflict(array, size);

			#pragma omp single
			resolve(array, size);

			#pragma omp single
			spawn(array, size, len, i);

			#pragma omp single
 	   		subAndCheckIfAlive(array, size);
		}
		#pragma omp barrier
		#pragma omp single
		end = omp_get_wtime();
		time = (end-start)*1000;
		
	}
	printf("Time(ms): %f\n",time);

	free(array);
	return 0;

}

void check_conflict(creature *array, int n){

		for(int i = 0; i < n - 1; i++){
			if(array[i].isPaired == -1 && array[i].aliveOrDead == 1){
				for(int j = i + 1; j < n; j++){
					if(array[i].xPos == array[j].xPos && array[i].yPos == array[j].yPos && array[j].aliveOrDead == 1){
						array[i].isPaired = j;
						array[j].isPaired = i;
					}
				}
			}
		}

}
void move( creature *array, int size, int len)
{
	unsigned int seed;
	seed = time(NULL);
	int i = 0;
	#pragma omp for
	for(i=0; i < size; i++){
		
		int xchange = (rand_r(&seed)%3) -1;
		int ychange = (rand_r(&seed)%3) -1;
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
	
}

int resolve( creature* array, int size)
{
	int i;
	int j =0;
	int killedOff = 0;
	for(i=0; i < size; i++){
		if(array[i].isPaired > -1){
			j = array[i].isPaired;
			if(array[j].isPaired == i){	//if paired with you then regular killing
				if(array[i].strength >= array[j].strength){
					array[j].aliveOrDead = 0;
					array[j].isPaired = -1;
					array[j].killedBy = i;

					array[i].isPaired = -1;
					array[i].lifetime += (array[j].lifetime)/4 ;
					killedOff += 1;
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;

					array[j].isPaired = -1;
					array[j].lifetime += (array[i].lifetime)/4;
					killedOff += 1;
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
					array[i].lifetime += (array[j].lifetime)/4;
					killedOff += 1;
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;

					array[j].isPaired = -1;
					array[j].lifetime += (array[i].lifetime)/4;
					killedOff += 1;

				}
			}
			
			
		}
	}
	return killedOff;
}
void spawn( creature *array, int size, int len, int iter)
{
	int i = 0;
	for(i=0; i < size; i++){

		if(array[i].aliveOrDead == 1 && (iter % array[i].fertility == 0))
		{
			for(int j = 0; j < size; j++)
			{
				if(array[j].aliveOrDead == 0)
				{
					// retain creature id
					array[j].strength = array[i].strength + (rand()%7) - 4;
					 
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
					if(array[j].strength > 127)
						array[j].strength = 127;
					else if(array[j].strength < 1)
						array[j].strength = 1;
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
              if(array[i].lifetime<=1){
                  array[i].lifetime = 0;
                  array[i].aliveOrDead = 0;
              }
              else{
                  array[i].lifetime--;
              }
        }
    }
}

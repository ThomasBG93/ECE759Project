#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "creature_char.h"

int main(int argc, char ** argv)
{
	if(argc != 3){
		printf("Usage: ./gen_file size creatureSize\n");
		exit(1);
	}
	int size = atoi(argv[1]);
	int numCreatures = atoi(argv[2]);
	FILE* fp;
	srand(time(NULL));  
    creature *array = (creature *)malloc(numCreatures * sizeof(creature));

	// strength level 0-10
	for(int i = 0; i < numCreatures ; i++){
		array[i].id = i;
		array[i].strength = ((double)rand()/(double)(RAND_MAX)) * 10;
		array[i].lifetime = rand() % 25 + 10;
		array[i].base_life = array[i].lifetime;
		array[i].fertility = rand() % 15 + 5;
		array[i].xPos = rand() % size; 
		array[i].yPos = rand() % size;
		array[i].isPaired = -1;
		array[i].killedBy = -1;
		//made minor change here
		if(i < numCreatures/2)
			array[i].aliveOrDead = 1;
		else 
			array[i].aliveOrDead = 0;
	}

	fp = fopen("input.txt", "w");
	if (fp == 0)
	{
		printf("Couldn't open file\n");
		exit(1);
	}

	for(int j =0; j < numCreatures; j++){
		fprintf(fp, "%d\n", array[j].id);
		fprintf(fp, "%f\n", array[j].strength);
		fprintf(fp, "%d\n", array[j].lifetime);
		fprintf(fp, "%d\n", array[j].base_life);
		fprintf(fp, "%d\n", array[j].fertility);
		fprintf(fp, "%d\n", array[j].aliveOrDead);
		fprintf(fp, "%d\n", array[j].isPaired);
		fprintf(fp, "%d\n", array[j].xPos);
		fprintf(fp, "%d\n", array[j].yPos);
		fprintf(fp, "%d\n", array[j].killedBy);
	}

	fclose(fp);
	//for(int i =0; i < numCreatures ; i++)
	//	free(array[i]);
	free(array);
	return 0;
}

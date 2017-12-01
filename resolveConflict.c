#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "creature_char.h"

int main(int argc, char *argv[])
{
	if(argc < 3){
		printf("Wrong input, should be: ./resolve length numCreatures\n");
		return 1;
	}
	int size = atoi(argv[2]); //numCreatures;
	int len = atoi(argv[1]);	//length of one side
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
		fscanf(fp, "%d\n", &array[i].killedBy);
	}
	int i;
	int j =0;
	for(i=0; i < size; i++){
		if(array[i].isPaired > -1){
			j = array[i].isPaired;
			if(array[j].isPaired == i){	//if paired with you then regular killing
				if(array[i].strength >= array[j].strength){
					array[j].aliveOrDead = 0;
					array[j].isPaired = -1;
					array[j].killedBy = i;
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;
				}
			}else{

				while(array[j].killedBy != -1){	//the guy you are paired with is already killed
					j = array[j].killedBy;
				}
				if(array[i].strength >= array[j].strength){
					array[j].aliveOrDead = 0;
					array[j].isPaired = -1;
					array[j].killedBy = i;
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;
				}
			}
			
			
		}
	}


}

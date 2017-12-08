#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <omp.h>
#include "creature_char.h"

int resolve( creature *array, int size);

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
	fp = fopen("out_check.txt", "r");
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

	int killedOff = resolve(array,size);

	fp = fopen("out_resolve.txt", "w");
	for(int i =0; i < size; i++){
		fprintf(fp, "%d\n", array[i].id);
		fprintf(fp, "%f\n", array[i].strength);
		fprintf(fp, "%d\n", array[i].lifetime);
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

int resolve( creature* array, int size)
{
	FILE* san;
	san = fopen("sanityResolve.txt","w");
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
					fprintf(san,"%d killed %d\n",i,j);
					//printf("%d killed %d\n",i,j);
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;

					array[j].isPaired = -1;
					array[j].lifetime += array[i].lifetime;
					killedOff += 1;
					fprintf(san,"%d killed %d\n",j,i);
					//printf("%d killed %d\n",j,i);
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
					fprintf(san,"%d killed %d\n",i,j);
					//printf("%d killed %d\n",i,j);
				}else{
					array[i].aliveOrDead = 0;
					array[i].isPaired = -1;
					array[i].killedBy = j;

					array[j].isPaired = -1;
					array[j].lifetime += array[i].lifetime;
					killedOff += 1;
					fprintf(san,"%d killed %d\n",j,i);
					//printf("%d killed %d\n",j,i);
				}
			}
			
			
		}
	}
	fclose(san);
	return killedOff;
}

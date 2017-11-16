#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "creature_char.h"

void check_confilct(creature *array, int n); 

int main(int argc, char** argv){
	assert(argc == 3);
	int size = atoi(argv[1]);
	int numCreatures = atoi(argv[2]);
	FILE* fp;
	creature *array = (creature *)malloc(numCreatures * sizeof(creature));
	fp = fopen("input.txt", "r");
	for(int j = 0; j < numCreatures; j++) {
		fscanf(fp, "%d\n", &array[j].id);
		fscanf(fp, "%lf\n", &array[j].strength);
		fscanf(fp, "%d\n", &array[j].lifetime);
		fscanf(fp, "%d\n", &array[j].fertility);
		fscanf(fp, "%d\n", &array[j].aliveOrDead);
		fscanf(fp, "%d\n", &array[j].isPaired);
		fscanf(fp, "%d\n", &array[j].xPos);
		fscanf(fp, "%d\n", &array[j].yPos);
	}
	fclose(fp);
	array[2].xPos= 2; array[2].yPos= 2; 
	array[4].xPos= 2; array[4].yPos= 2;
	check_confilct(array, numCreatures);
	fp = fopen("test.txt", "w");
	for(int j =0; j < numCreatures; j++){
		fprintf(fp, "%d\n", array[j].id);
		fprintf(fp, "%f\n", array[j].strength);
		fprintf(fp, "%d\n", array[j].lifetime);
		fprintf(fp, "%d\n", array[j].fertility);
		fprintf(fp, "%d\n", array[j].aliveOrDead);
		fprintf(fp, "%d\n", array[j].isPaired);
		fprintf(fp, "%d\n", array[j].xPos);
		fprintf(fp, "%d\n", array[j].yPos);
	}
	fclose(fp);


	free(array);
	return 0;
}
// accepts the array of creatures and 
void check_confilct(creature *array, int n){
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
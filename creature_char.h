#ifndef _CHAR_C_H
#define _CHAR_C_H

typedef struct {
	int id;
	double strength;
	int lifetime; 
	int fertility; // defined by the movement
	int aliveOrDead; // 1 is alive and 0 is dead
	int isPaired; // check if in conflict with another object
	int xPos;
	int yPos;
}creature;

// list header types below here

// move 

// checkConflict

// resolveConflict

// spawn

// writeMatrix

// saveState


#endif

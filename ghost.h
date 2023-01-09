#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include "structs.h"
#include <cstdlib>

using namespace std;

struct Ghost{
	Coords coords;
	int velocity;
	char direction;
	int previousStatus;
};


void moveGhost(int **&ground, Ghost &ghost, int &previousStatus, bool &pacmanCheck){
	while(isThereWall(ground, ghost.coords, ghost.direction)){   
		int random = rand() % 4;
		char newDirection;
		switch(random){
		case 0:
			newDirection = 'w';
			break;
		case 1:
			newDirection = 's';
			break;
		case 2:
			newDirection = 'd';
			break;
		case 3:
			newDirection = 'a';
			break;
		}
		ghost.direction = newDirection;
	}
	
	switch (ghost.direction){
	case 'w':
		if(!isThereWall(ground, ghost.coords, 'w')){
		    ground[ghost.coords.i][ghost.coords.j] = previousStatus;
		    ghost.coords.i--;
		    if(ground[ghost.coords.i][ghost.coords.j] != -2 && ground[ghost.coords.i][ghost.coords.j] != 2){
		    	previousStatus = ground[ghost.coords.i][ghost.coords.j];
		    }
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2){       
		    	pacmanCheck = 1;
		    }
		    ground[ghost.coords.i][ghost.coords.j] = -2;
		}
        	break;
       case 's':
		if(!isThereWall(ground, ghost.coords, 's')){
		    ground[ghost.coords.i][ghost.coords.j] = previousStatus;
		    ghost.coords.i++;
		    if(ground[ghost.coords.i][ghost.coords.j] != -2 && ground[ghost.coords.i][ghost.coords.j] != 2){
		    	previousStatus = ground[ghost.coords.i][ghost.coords.j];
		    }
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2){
		    	pacmanCheck = 1;
		    }
		    ground[ghost.coords.i][ghost.coords.j] = -2;
		}
		break;
       case 'd':
		if(!isThereWall(ground, ghost.coords, 'd')){
		    ground[ghost.coords.i][ghost.coords.j] = previousStatus;
		    ghost.coords.j++;
		    if(ground[ghost.coords.i][ghost.coords.j] != -2 && ground[ghost.coords.i][ghost.coords.j] != 2){
		    	previousStatus = ground[ghost.coords.i][ghost.coords.j];
		    }
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2){
		    	pacmanCheck = 1;
		    }
		    ground[ghost.coords.i][ghost.coords.j] = -2;
		}
		break;
       case 'a':
		if(!isThereWall(ground, ghost.coords, 'a')){
		    ground[ghost.coords.i][ghost.coords.j] = previousStatus;
		    ghost.coords.j--;
		    if(ground[ghost.coords.i][ghost.coords.j] != -2 && ground[ghost.coords.i][ghost.coords.j] != 2){
		    	previousStatus = ground[ghost.coords.i][ghost.coords.j];
		    }
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2){
		    	pacmanCheck = 1;
		    }
		    ground[ghost.coords.i][ghost.coords.j] = -2;
		}
		break;
    }
	
	
}

void choosegDirection(){
}

int stVelocity(int level){
}

#endif

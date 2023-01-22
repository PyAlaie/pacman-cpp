#include <iostream>
#include <cstdlib>
#include "ghost.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace std;

void 
Ghost::move(int **&ground, int &previousStatus, bool &pacmanCheck){
	while(isThereWall(ground, coords, direction)){   
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
		direction = newDirection;
	}
	
	switch (direction){
	case 'w':
		if(!isThereWall(ground, coords, 'w')){
		    ground[coords.i][coords.j] = previousStatus;
		    coords.i--;
		    if(ground[coords.i][coords.j] != -2 && ground[coords.i][coords.j] != 2){
		    	previousStatus = ground[coords.i][coords.j];
		    }
		    else if(ground[coords.i][coords.j] == 2 || previousStatus == 2){       
		    	pacmanCheck = 1;
		    }
		    ground[coords.i][coords.j] = -2;
		}
        	break;
       case 's':
		if(!isThereWall(ground, coords, 's')){
		    ground[coords.i][coords.j] = previousStatus;
		    coords.i++;
		    if(ground[coords.i][coords.j] != -2 && ground[coords.i][coords.j] != 2){
		    	previousStatus = ground[coords.i][coords.j];
		    }
		    else if(ground[coords.i][coords.j] == 2 || previousStatus == 2){
		    	pacmanCheck = 1;
		    }
		    ground[coords.i][coords.j] = -2;
		}
		break;
       case 'd':
		if(!isThereWall(ground, coords, 'd')){
		    ground[coords.i][coords.j] = previousStatus;
		    coords.j++;
		    if(ground[coords.i][coords.j] != -2 && ground[coords.i][coords.j] != 2){
		    	previousStatus = ground[coords.i][coords.j];
		    }
		    else if(ground[coords.i][coords.j] == 2 || previousStatus == 2){
		    	pacmanCheck = 1;
		    }
		    ground[coords.i][coords.j] = -2;
		}
		break;
       case 'a':
		if(!isThereWall(ground, coords, 'a')){
		    ground[coords.i][coords.j] = previousStatus;
		    coords.j--;
		    if(ground[coords.i][coords.j] != -2 && ground[coords.i][coords.j] != 2){
		    	previousStatus = ground[coords.i][coords.j];
		    }
		    else if(ground[coords.i][coords.j] == 2 || previousStatus == 2){
		    	pacmanCheck = 1;
		    }
		    ground[coords.i][coords.j] = -2;
		}
		break;
    }
	
	
}
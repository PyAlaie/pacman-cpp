#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include "structs.h"
#include <cstdlib>
#include <cmath>

using namespace std;

struct Ghost{
	Coords coords;
	Coords targetPoint;
	bool dirStatus[4]; //0 for w, 1 for d, 2 for s and 3 for a
	char mode;  //s for scatter, c for chase and e for deadwalk
	int velocity;
	char direction;
	int previousStatus;
};
int getDist(Coords targetPoint, int dir, Coords ghostCoords){
	int dist = 0;
	switch (dir)
	{
	case 0:
		dist = pow(targetPoint.i - (ghostCoords.i + 1), 2) + pow(targetPoint.j - ghostCoords.j, 2); 
		break;
	case 1:
		dist = pow(targetPoint.i - ghostCoords.i, 2) + pow(targetPoint.j - (ghostCoords.j + 1), 2); 
		break;
	case 2:
		dist = pow(targetPoint.i - ghostCoords.i, 2) + pow(targetPoint.j - (ghostCoords.j - 1), 2); 
		break;
	case 3:
		dist = pow(targetPoint.i - (ghostCoords.i - 1), 2) + pow(targetPoint.j - ghostCoords.j, 2); 
		break;	
	}

	dist = sqrt(dist);
	return dist;
}

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
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2 || previousStatus == 2){       
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
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2 || previousStatus == 2){
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
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2 || previousStatus == 2){
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
		    else if(ground[ghost.coords.i][ghost.coords.j] == 2 || previousStatus == 2){
		    	pacmanCheck = 1;
		    }
		    ground[ghost.coords.i][ghost.coords.j] = -2;
		}
		break;
    }
	
	
}

void move(int **&map, Coords &ghostCoords, char dir, int &previousStatus){
	switch (dir)
	{
	case 'w':
		map[ghostCoords.i][ghostCoords.j] = previousStatus;
		ghostCoords.i++;
		map[ghostCoords.i][ghostCoords.j] = -2;
		if(map[ghostCoords.i][ghostCoords.j] != -2 && map[ghostCoords.i][ghostCoords.j] != 2){
		    	previousStatus = map[ghostCoords.i][ghostCoords.j];
		}
		break;
	case 'd':
		map[ghostCoords.i][ghostCoords.j] = previousStatus;
		ghostCoords.j++;
		map[ghostCoords.i][ghostCoords.j] = -2;
		if(map[ghostCoords.i][ghostCoords.j] != -2 && map[ghostCoords.i][ghostCoords.j] != 2){
		    	previousStatus = map[ghostCoords.i][ghostCoords.j];
		}
		break;
	case 's':
		map[ghostCoords.i][ghostCoords.j] = previousStatus;
		ghostCoords.i--;
		map[ghostCoords.i][ghostCoords.j] = -2;
		if(map[ghostCoords.i][ghostCoords.j] != -2 && map[ghostCoords.i][ghostCoords.j] != 2){
		    	previousStatus = map[ghostCoords.i][ghostCoords.j];
		}
		break;
	case 'a':
		map[ghostCoords.i][ghostCoords.j] = previousStatus;
		ghostCoords.j--;
		map[ghostCoords.i][ghostCoords.j] = -2;
		if(map[ghostCoords.i][ghostCoords.j] != -2 && map[ghostCoords.i][ghostCoords.j] != 2){
		    	previousStatus = map[ghostCoords.i][ghostCoords.j];
		}
		break;
	}

}

char chooseDirection(bool *&dirStatus, Coords targetPoint, Coords ghostCoords, char currentDir){ //chooses the shortest path dir
	int minDist = 0;
	bool flag = 1;
	int dir = 4;

	for(int i = 0; i < 4; i++){
		int temp;
		if(dirStatus[i]){
			temp = getDist(targetPoint, i, ghostCoords);
			if(flag || minDist < temp){
				minDist = temp;
				dir = i;
			}
		}
	}

	switch (dir){
	case 1:
		return 'w';
		break;	
	case 2:
		return 'd';
		break;
	case 3:
		return 's';
		break;
	case 4:
		return 'a';
		break;
	}
	return currentDir;
}

void validDirections(int **map, Coords ghostCoords, bool *&dirStatus, char currentDir){
	switch (currentDir)
	{
	case 'w':
		dirStatus[2] = 0;
		break;
	case 'a':
		dirStatus[1] = 0;
		break;
	case 'd':
		dirStatus[3] = 0;
		break;
	case 's':
		dirStatus[0] = 0;
		break;
	}
	if(isThereWall(map, ghostCoords, 'w')){
		dirStatus[0] = 0;
	} else if(isThereWall(map, ghostCoords, 'd')){
		dirStatus[1] = 0;
	} else if(isThereWall(map, ghostCoords, 's')){
		dirStatus[2] = 0;
	}else if(isThereWall(map, ghostCoords, 'a')){
		dirStatus[3] = 0;
	}
}

void chooseTargetPoint(Ghost &ghost, int ghostNumber, Coords pacman, int n, int m, char pacmanDir,
						 Coords blinky, Coords pinkyTargetPoint){
	
	int xDist = abs(blinky.i - pinkyTargetPoint.i);
	int yDist = abs(blinky.j - pinkyTargetPoint.j);
	
	if(ghost.mode == 's'){
		switch (ghostNumber)
		{
		case 1:
			if(ghost.targetPoint.i == n - 2 && ghost.targetPoint.j == m - 2 &&
			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 1){ 
				int random = rand();
				ghost.targetPoint.i = random % (n-1);
				ghost.targetPoint.j = random % (m-1);
			 } else if(!(ghost.targetPoint.i == n - 2 && ghost.targetPoint.j == m - 2) &&
			 			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){ //target point: bottom right
						ghost.targetPoint.i = n - 2;
						ghost.targetPoint.j = m - 2;
					}
			break;

		case 2:
			if(ghost.targetPoint.i == 1 && ghost.targetPoint.j == m - 2 &&
			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 1){ 
				int random = rand();
				ghost.targetPoint.i = random % (n-1);
				ghost.targetPoint.j = random % (m-1);
			 } else if(!(ghost.targetPoint.i == 1 && ghost.targetPoint.j == m - 2) &&
			 			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){ //target point: top right
						ghost.targetPoint.i = 1;
						ghost.targetPoint.j = m - 2;
					}
			break;

		case 3:
			if(ghost.targetPoint.i == 1 && ghost.targetPoint.j == 1 &&
			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 1){
				int random = rand();
				ghost.targetPoint.i = random % (n-1);
				ghost.targetPoint.j = random % (m-1);
			 } else if(!(ghost.targetPoint.i == 1 && ghost.targetPoint.j == 2) &&
			 			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){//target point: top left
						ghost.targetPoint.i = 1;
						ghost.targetPoint.j = 1;
					}
			break;

		case 4:
			if(ghost.targetPoint.i == n - 2 && ghost.targetPoint.j == 1 &&
			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 1){
				int random = rand();
				ghost.targetPoint.i = random % (n-1);
				ghost.targetPoint.j = random % (m-1);
			 } else if(!(ghost.targetPoint.i == n - 1 && ghost.targetPoint.j == 1) &&
			 			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){//target point: bottom left
						ghost.targetPoint.i = n - 2;
						ghost.targetPoint.j = 1;
					}
			break;
		}
	}

	if(ghost.mode == 'c'){
		switch (ghostNumber)
		{
		case 1:
			ghost.targetPoint.i = pacman.i;
			ghost.targetPoint.j = pacman.j;
			break;
		case 2:
			if(pacmanDir == 'w'){
				ghost.targetPoint.i = pacman.i + 2;
				ghost.targetPoint.j = pacman.j + 2;
			}	else if(pacmanDir == 'd'){
				ghost.targetPoint.i = pacman.i;
				ghost.targetPoint.j = pacman.j + 2;
			} else if(pacmanDir == 's'){
				ghost.targetPoint.i = pacman.i;
				ghost.targetPoint.j = pacman.j - 2;
			} else if(pacmanDir == 'a'){
				ghost.targetPoint.i = pacman.i - 2;
				ghost.targetPoint.j = pacman.j;
			}
			break;
		case 3:
			if(blinky.i > pinkyTargetPoint.i){		//flip bliky.i respect to pinkyTragetpoin.i in 180 degree
				ghost.targetPoint.i = pinkyTargetPoint.i - xDist;
			} else{
				ghost.targetPoint.i = pinkyTargetPoint.i + xDist;
			}

			if(blinky.j > pinkyTargetPoint.j){ //flip bliky.i respect to pinkyTragetpoin.j in 180 degree
				ghost.targetPoint.j = pinkyTargetPoint.j - yDist;
			} else{
				ghost.targetPoint.j = pinkyTargetPoint.j + yDist;
			}
			break;
		

		case 4:
			if(getDist(pacman, ghost.direction, ghost.coords) <= 8){
				ghost.targetPoint.i = pacman.i;
				ghost.targetPoint.j = pacman.j;
			} else if(ghost.targetPoint.i == n - 2 && ghost.targetPoint.j == 1 &&
				getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 1){  //switch to scatter mode movement
					int random = rand();
					ghost.targetPoint.i = random % (n-1);
					ghost.targetPoint.j = random % (m-1);
			} else if(!(ghost.targetPoint.i == n - 1 && ghost.targetPoint.j == 1) &&
						getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){
						ghost.targetPoint.i = n - 2;
						ghost.targetPoint.j = 1;
					}
			break;
		}
	}
}

#endif
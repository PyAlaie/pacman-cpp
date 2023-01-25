#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include "structs.h"
#include <cstdlib>
#include <cmath>
#include <vector>
#include <algorithm>
#include <map>
#include <queue>

using namespace std;

struct Ghost{
	Coords coords;
	Coords targetPoint;
	char mode;  //s for scatter, c for chase and e for deadwalk
	int velocity;
	char direction;
	int previousStatus;
	vector<Coords> path;
};

void setDir(vector<bool> &dirStatus){
	for(unsigned int i = 0; i < 4; i++){
		dirStatus[i] = true;
   }
}
int getDist(Coords targetPoint, int dir, Coords ghostCoords){
	int dist = 0;
	switch (dir)
	{
	case 0:
		dist = pow(targetPoint.i - (ghostCoords.i - 1), 2) + pow(targetPoint.j - ghostCoords.j, 2); 
		break;
	case 1:
		dist = pow(targetPoint.i - ghostCoords.i, 2) + pow(targetPoint.j - (ghostCoords.j + 1), 2); 
		break;
	case 2:
		dist = pow(targetPoint.i - (ghostCoords.i + 1), 2) + pow(targetPoint.j - ghostCoords.j, 2); 
		break;
	case 3:
		dist = pow(targetPoint.i - ghostCoords.i, 2) + pow(targetPoint.j - (ghostCoords.j - 1), 2); 
		break;	
	}

	dist = (int)	sqrt(dist);
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
bool isValidDirection(int **map, Coords ghostCoords, char currentDir, char inputDir){
	if(isThereWall(map, ghostCoords, inputDir)){
		return false;
	}

	// if((inputDir == 'w' && currentDir == 's') ||
	// 	 (inputDir == 's' && currentDir == 'w') ||
	// 	 (inputDir == 'a' && currentDir == 'd') ||
	// 	 (inputDir == 'd' && currentDir == 'a') ){
	// 		return false;
	// 	 }
	return true;

}

void move(int **&map, Ghost &ghost){
	switch (ghost.direction)
	{
	case 'w':
		map[ghost.coords.i][ghost.coords.j] = ghost.previousStatus;
		ghost.coords.i--;
		// ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		if(map[ghost.coords.i][ghost.coords.j] != -2 && map[ghost.coords.i][ghost.coords.j] != 2){
		    	ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		}
		map[ghost.coords.i][ghost.coords.j] = -2;
		break;
	case 'd':
		map[ghost.coords.i][ghost.coords.j] = ghost.previousStatus;
		ghost.coords.j++;
		// ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		if(map[ghost.coords.i][ghost.coords.j] != -2 && map[ghost.coords.i][ghost.coords.j] != 2){
		    	ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		}
		map[ghost.coords.i][ghost.coords.j] = -2;
		break;
	case 's':
		map[ghost.coords.i][ghost.coords.j] = ghost.previousStatus;
		ghost.coords.i++;
		// ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		if(map[ghost.coords.i][ghost.coords.j] != -2 && map[ghost.coords.i][ghost.coords.j] != 2){
		    	ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		}
		map[ghost.coords.i][ghost.coords.j] = -2;
		break;
	case 'a':
		map[ghost.coords.i][ghost.coords.j] = ghost.previousStatus;
		ghost.coords.j--;	
		// ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		if(map[ghost.coords.i][ghost.coords.j] != -2 && map[ghost.coords.i][ghost.coords.j] != 2){
		    	ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		}
		map[ghost.coords.i][ghost.coords.j] = -2;
		break;
	}

}

char chooseDirection(int **map, Coords targetPoint, Coords ghostCoords, char currentDir){ //chooses the shortest path dir
	/*int minDist = 0;
	bool flag = 1;
	char dir = 'w';
	int direction = 4;

	for(int i = 0; i < 4; i++){
		int temp;
		switch(i){
			case 0:
				dir = 'w';
				break;
			case 1:
				dir = 'd';
				break;
			case 2:
				dir = 's';
				break;
			case 3:
				dir = 'a';
				break;
		}
		if(isValidDirection(map, ghostCoords, currentDir, dir)){
			temp = getDist(targetPoint, i, ghostCoords);
			if(flag || minDist < temp){
				flag = 0;
				minDist = temp;
				direction = i;
			}
		}
	}

	switch (direction){
	case 0:
		return 'w';
		break;	
	case 1:
		return 'd';
		break;
	case 2:
		return 's';
		break;
	case 3:
		return 'a';
		break;
	}
	return currentDir;*/
}

bool isNotVisited(Coords x, vector<Coords>& explored){
	for(int i = 0; i < explored.size(); i++){
		// cout << "POINT: " << x.i << "	" << x.j << endl << endl;
		// cout << "EXPLORED: " << explored[i].i <<"	"<< explored[i].j << endl;
		if(explored[i] == x)
			return 0;
	}
	return 1;
}

void findpaths(int **map, Coords src, Coords dst, vector<Coords>& path)
{
    path.clear();
    char directions[4] = {'w', 'd', 's', 'a'};
    // create a queue which stores
    // the paths
    queue<vector<Coords> > q;
 
    // path vector to store the current path
    // vector<Coords> path;
    path.push_back(src);
    q.push(path);
    while (!q.empty()) {
        path = q.front();
        q.pop();
        Coords last = path[path.size() - 1];
 
        // if last vertex is the desired destination
        // then print the path
        if (last == dst){
            // return path;
            break;
        }
 

 
        // traverse to all the nodes connected to
        // current vertex and push new path to queue
        for (int i = 0; i < 4; i++) {
            Coords childCell;
            if(!isThereWall(map, last, directions[i])){
	// cout << "BIROON " << currentCell.i << "  " << currentCell.j << endl;
				if(directions[i] == 'w'){
					childCell.i = last.i - 1;
					childCell.j = last.j; 
				} else if(directions[i] == 'd'){
					childCell.i = last.i;
					childCell.j = last.j + 1; 
				} else if(directions[i] == 's'){
					childCell.i = last.i + 1;
					childCell.j = last.j; 
				} else if(directions[i] == 'a'){
					childCell.i = last.i;
					childCell.j = last.j - 1; 
				}
            if (isNotVisited(childCell, path)) {
                vector<Coords> newpath(path);
                newpath.push_back(childCell);
                q.push(newpath);
            }
        }
    }
}
}


void newMove(int **&map, Ghost &ghost, Coords target){
	map[ghost.coords.i][ghost.coords.j] = ghost.previousStatus;
	if(map[ghost.coords.i][ghost.coords.j] != -2 && map[ghost.coords.i][ghost.coords.j] != 2){
		    	ghost.previousStatus = map[ghost.coords.i][ghost.coords.j];
		}
	map[target.i][target.j] = -2;
	ghost.coords = target;

}

Coords chooseTargetPoint(Ghost ghost, int ghostNumber, Coords pacman, int n, int m, char pacmanDir,
						 Coords blinky, Coords pinkyTargetPoint){
	
	int xDist = abs(blinky.i - pinkyTargetPoint.i);
	int yDist = abs(blinky.j - pinkyTargetPoint.j);
	
	Coords newTargetPoint = ghost.targetPoint;
	if(ghost.mode == 's'){
		switch(ghostNumber){
			case 1:
				newTargetPoint.i = n - 1;
				newTargetPoint.j = m - 1;
				break;
			case 2:
				newTargetPoint.i = n - 2;
				newTargetPoint.j = m - 2;
				break;
			case 3:
				newTargetPoint.i = n - 2;
				newTargetPoint.j = m - 2;
				break;
			case 4:
				newTargetPoint.i = n - 2;
				newTargetPoint.j = m - 2;
				break;
		}
	}
	// ghost.mode = 'c';
	// if(ghost.mode == 's'){
	// 	switch (ghostNumber)
	// 	{
	// 	case 1:
	// 		newTargetPoint.i = n - 2;
	// 		newTargetPoint.j = m - 2;
	// 		// if(ghost.targetPoint.i == n - 2 || ghost.targetPoint.j == m - 2 ||
	// 		//  getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){ 
	// 		// 	int random = rand();
	// 		// 	newTargetPoint.i = random % (n-1);
	// 		// 	newTargetPoint.j = random % (m-1);
	// 		//  			usleep(1000000);
	// 		//  } else if(!(ghost.targetPoint.i == n - 2 || ghost.targetPoint.j == m - 2) ||
	// 		//  			getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){ //target point: bottom right
	// 		// 			newTargetPoint.i = n - 2;
	// 		// 			newTargetPoint.j = m - 2;
	// 		// 		}
	// 		break;

	// 	case 2:
	// 		newTargetPoint.i = 1;
	// 		newTargetPoint.j = m - 2;
	// 		// if(ghost.targetPoint.i == 1 && ghost.targetPoint.j == m - 2 &&
	// 		//  getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){ 
	// 		// 	int random = rand();
	// 		// 	newTargetPoint.i = random % (n-1);
	// 		// 	newTargetPoint.j = random % (m-1);
	// 		//  } else if(!(ghost.targetPoint.i == 1 && ghost.targetPoint.j == m - 2) &&
	// 		//  			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){ //target point: top right
	// 		// 			newTargetPoint.i = 1;
	// 		// 			newTargetPoint.j = m - 2;
	// 		// 		}
	// 		break;

	// 	case 3:
	// 		newTargetPoint.i = 1;
	// 		newTargetPoint.j = 1;
	// 		// if(ghost.targetPoint.i == 1 && ghost.targetPoint.j == 1 &&
	// 		//  getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){
	// 		// 	int random = rand();
	// 		// 	newTargetPoint.i = random % (n-1);
	// 		// 	newTargetPoint.j = random % (m-1);
	// 		//  } else if(!(ghost.targetPoint.i == 1 && ghost.targetPoint.j == 2) &&
	// 		//  			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){//target point: top left
	// 		// 			newTargetPoint.i = 1;
	// 		// 			newTargetPoint.j = 1;
	// 		// 		}
	// 		break;

	// 	case 4:
	// 		newTargetPoint.i = n - 2;
	// 		newTargetPoint.j = 1;
	// 		// if(ghost.targetPoint.i == n - 2 && ghost.targetPoint.j == 1 &&
	// 		//  getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){
	// 		// 	int random = rand();
	// 		// 	newTargetPoint.i = random % (n-1);
	// 		// 	newTargetPoint.j = random % (m-1);
	// 		//  } else if(!(ghost.targetPoint.i == n - 1 && ghost.targetPoint.j == 1) &&
	// 		//  			 getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){//target point: bottom left
	// 		// 			newTargetPoint.i = n - 2;
	// 		// 			newTargetPoint.j = 1;
	// 		// 		}
	// 		break;
	// 	}
	// }

	//  else if(ghost.mode == 'c'){
		newTargetPoint.i = pacman.i;
		newTargetPoint.j = pacman.j;
		// switch (ghostNumber)
		// {
		// case 1:
		// 	newTargetPoint.i = pacman.i;
		// 	newTargetPoint.j = pacman.j;
		// 	break;
		// case 2:
		// 	if(pacmanDir == 'w'){
		// 		newTargetPoint.i = pacman.i + 2;
		// 		newTargetPoint.j = pacman.j + 2;
		// 	}	else if(pacmanDir == 'd'){
		// 		newTargetPoint.i = pacman.i;
		// 		newTargetPoint.j = pacman.j + 2;
		// 	} else if(pacmanDir == 's'){
		// 		newTargetPoint.i = pacman.i;
		// 		newTargetPoint.j = pacman.j - 2;
		// 	} else if(pacmanDir == 'a'){
		// 		newTargetPoint.i = pacman.i - 2;
		// 		newTargetPoint.j = pacman.j;
		// 	}
		// 	break;
		// case 3:
		// 	if(blinky.i > pinkyTargetPoint.i){		//flip bliky.i respect to pinkyTragetpoin.i in 180 degree
		// 		newTargetPoint.i = pinkyTargetPoint.i - xDist;
		// 	} else{
		// 		newTargetPoint.i = pinkyTargetPoint.i + xDist;
		// 	}

		// 	if(blinky.j > pinkyTargetPoint.j){ //flip bliky.i respect to pinkyTragetpoin.j in 180 degree
		// 		newTargetPoint.j = pinkyTargetPoint.j - yDist;
		// 	} else{
		// 		newTargetPoint.j = pinkyTargetPoint.j + yDist;
		// 	}
		// 	break;
		

		// case 4:
		// 	if(getDist(pacman, ghost.direction, ghost.coords) <= 8){
		// 		newTargetPoint.i = pacman.i;
		// 		newTargetPoint.j = pacman.j;
		// 	} else if(ghost.targetPoint.i == n - 2 && ghost.targetPoint.j == 1 &&
		// 		getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 1){  //switch to scatter mode movement
		// 			int random = rand();
		// 			newTargetPoint.i = random % (n-1);
		// 			newTargetPoint.j = random % (m-1);
		// 	} else if(!(ghost.targetPoint.i == n - 1 && ghost.targetPoint.j == 1) &&
		// 				getDist(ghost.targetPoint, ghost.direction, ghost.coords) <= 3){
		// 				newTargetPoint.i = n - 2;
		// 				newTargetPoint.j = 1;
		// 			}
		// 	break;
		// }
	// }

	return newTargetPoint;
}



void updateGhostDirection(int ** map, Ghost &g){
	int wallsAround = 0;

	// 0w 1d 2s 3a
	bool directions[4] = {true,true,true,true};

	switch (g.direction)
	{
	case 'w':
		directions[2] = false;
		break;
	case 's':
		directions[0] = false;
		break;
	case 'd':
		directions[3] = false;
		break;
	case 'a':
		directions[1] = false;
		break;
	}

	if(map[g.coords.i+1][g.coords.j] == 1){wallsAround++; directions[2] = false;}
	if(map[g.coords.i-1][g.coords.j] == 1){wallsAround++; directions[0] = false;}
	if(map[g.coords.i][g.coords.j+1] == 1){wallsAround++; directions[1] = false;}
	if(map[g.coords.i][g.coords.j-1] == 1){wallsAround++; directions[3] = false;}

	vector<char> d;
	if(directions[0] == true){d.push_back('w');}
	if(directions[1] == true){d.push_back('d');}
	if(directions[2] == true){d.push_back('s');}
	if(directions[3] == true){d.push_back('a');}

	if(wallsAround <= 1){
		// usleep(3000000);
		int temp = rand() % d.size();
		char randDirection = d[temp];
		g.direction = randDirection;
		return;
	}
	else if (isThereWall(map, g.coords,g.direction)){
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

		while(isThereWall(map, g.coords, newDirection)){   
			random = rand() % 4;
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
		}
		g.direction = newDirection;
	}

}

#endif
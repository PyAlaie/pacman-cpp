#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>
#include "structs.h"
#include <cstdlib>

using namespace std;

struct Pacman{
    Coords coords;
    int lives;
    char current_direction;
    char input_direction;
    void updatePacmanDirection(int **arr, Pacman &pacman, bool &pacmanCheck);
    void movePacman(int **&arr, Pacman &pacman);
};

void updatePacmanDirection(int **arr, Pacman &pacman){   
    if(!isThereWall(arr,pacman.coords,pacman.input_direction)){
        pacman.current_direction = pacman.input_direction;
    }
}

void movePacman(int **&arr, Pacman &pacman, bool &pacmanCheck){   
    switch (pacman.current_direction)
    {
    case 'w':
        if(!isThereWall(arr, pacman.coords, 'w')){
            arr[pacman.coords.i][pacman.coords.j] = -1;
            pacman.coords.i--;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        }
        break;
    case 's':
        if(!isThereWall(arr, pacman.coords, 's')){
            arr[pacman.coords.i][pacman.coords.j] = -1;
            pacman.coords.i++;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        }
        break;
    case 'd':
        if(!isThereWall(arr, pacman.coords, 'd')){
            arr[pacman.coords.i][pacman.coords.j] = -1;
            pacman.coords.j++;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        }
        break;
    case 'a':
        if(!isThereWall(arr, pacman.coords, 'a')){
            arr[pacman.coords.i][pacman.coords.j] = -1;
            pacman.coords.j--;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        }
        break;
    }
}

#endif

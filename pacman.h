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
    bool movePacman(int **&arr, Pacman &pacman);
};

void updatePacmanDirection(int **arr, Pacman &pacman){   
    if(!isThereWall(arr,pacman.coords,pacman.input_direction)){
        pacman.current_direction = pacman.input_direction;
    }
}

bool movePacman(int **&arr, Pacman &pacman, bool &pacmanCheck, bool &cherryCheck, int &cherryTime){   
    switch (pacman.current_direction)
    {
    case 'w':
        if(!isThereWall(arr, pacman.coords, 'w')){
            if(isThereCherry(arr, pacman.coords, 'w')){
                cherryCheck = 1;
                cherryTime = 50;
            }
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
                arr[pacman.coords.i][pacman.coords.j] = -1;
            }
            else{
                pacmanCheck = 1;
            }
            pacman.coords.i--;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	        }
	        else{
	        	pacmanCheck = 1;
	        }
            return true;
        }
        break;
    case 's':
        if(!isThereWall(arr, pacman.coords, 's')){
            if(isThereCherry(arr, pacman.coords, 's')){
                cherryCheck = 1;
                cherryTime = 50;
            }
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
                arr[pacman.coords.i][pacman.coords.j] = -1;
            }
            else{
                pacmanCheck = 1;
            }
            pacman.coords.i++;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        return true;
        }
        break;
    case 'd':
        if(isThereCherry(arr, pacman.coords, 'd')){
                    cherryCheck = 1;
                    cherryTime = 50;
                }
        if(!isThereWall(arr, pacman.coords, 'd')){
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
                arr[pacman.coords.i][pacman.coords.j] = -1;
            }
            else{
                pacmanCheck = 1;
            }
            pacman.coords.j++;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        return true;
        }
        break;
    case 'a':
        if(!isThereWall(arr, pacman.coords, 'a')){
            if(isThereCherry(arr, pacman.coords, 'a')){
                cherryCheck = 1;
                cherryTime = 50;
            }
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
                arr[pacman.coords.i][pacman.coords.j] = -1;
            }
            else{
                pacmanCheck = 1;
            }
            pacman.coords.j--;
            if(arr[pacman.coords.i][pacman.coords.j] != -2){
	            arr[pacman.coords.i][pacman.coords.j] = 2;
	    }
	    else{
	    	pacmanCheck = 1;
	    }
        return true;
        }
        break;
    }
}

#endif

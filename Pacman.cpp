#include <iostream>
#include "pacman.h"
#include <cstdlib>

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

using namespace std;

void 
Pacman::updateDirection(int **arr, Pacman &pacman){   
    if(!isThereWall(arr,pacman.coords,pacman.input_direction)){
        pacman.current_direction = pacman.input_direction;
    }
}

void 
Pacman::move(int **&arr, Pacman &pacman, bool &pacmanCheck){   
    switch (pacman.current_direction)
    {
    case 'w':
        if(!isThereWall(arr, pacman.coords, 'w')){
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
        }
        break;
    case 's':
        if(!isThereWall(arr, pacman.coords, 's')){
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
        }
        break;
    case 'd':
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
        }
        break;
    case 'a':
        if(!isThereWall(arr, pacman.coords, 'a')){
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
        }
        break;
    }
}

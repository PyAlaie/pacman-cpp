#ifndef STRUCTS_H 
#define STRUCTS_H

#include <iostream>
#include <cmath>

using namespace std;

struct Coords
{
    int i;
    int j;
};

void setTime(int &scatterTime, int &chaseTime, int choosenLevel){
    if(choosenLevel == 1){
        scatterTime = 100;
        chaseTime = 200;
    }
    else if(choosenLevel == 2){
        scatterTime = 150;
        chaseTime = 100;
    }
    else{
        scatterTime = 150;
        chaseTime = 150;
    }
}




bool isThereWall(int **arr, Coords coords, char direction){   
    switch (direction)
    {
    case 'w':
        if(arr[coords.i - 1][coords.j] == 1){
            return true;
        }
        return false;
        break;
    case 's':
        if(arr[coords.i + 1][coords.j] == 1){
            return true;
        }
        return false;
        break;
    case 'd':
        if(arr[coords.i][coords.j + 1] == 1){
            return true;
        }
        return false;
        break;
    case 'a':
        if(arr[coords.i][coords.j - 1] == 1){
            return true;
        }
        return false;
        break;
    }
}

bool isThereCherry(int **arr, Coords coords, char direction){   
    switch (direction)
    {
    case 'w':
        if(arr[coords.i - 1][coords.j] == 3){
            return true;
        }
        return false;
        break;
    case 's':
        if(arr[coords.i + 1][coords.j] == 3){
            return true;
        }
        return false;
        break;
    case 'd':
        if(arr[coords.i][coords.j + 1] == 3){
            return true;
        }
        return false;
        break;
    case 'a':
        if(arr[coords.i][coords.j - 1] == 3){
            return true;
        }
        return false;
        break;
    }
}

bool ghostCheck(Coords pacman, Coords ghost){
    Coords minCoor;
    int dist = 0, xDist, yDist;
    xDist = (ghost.i - pacman.i)* (ghost.i - pacman.i);
    yDist = (ghost.j - pacman.j) * (ghost.j - pacman.j);
    dist = sqrt(xDist + yDist);
    if(dist <= 1){
        return true;
    }
    return false;

}

int calScore(int dotCounter, int ghostCounter, int cherryCount){
    int score = 0;
    cherryCount *= 5;
    ghostCounter *= 10;
    score += dotCounter;
    score += cherryCount;
    score += ghostCounter;
    return score;
}

#endif
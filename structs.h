#ifndef STRUCTS_H 
#define STRUCTS_H

#include <iostream>
#include <cmath>

using namespace std;

struct Coords
{
    int i;
    int j;
    bool isThereWall(int **arr, Coords coords, char direction);
    bool pacmanCheck(int **&map, char pacmanDir, char ghostDir);
};


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

int score(int time, int dotCounter, int ghostCounter){
    int score = 0;
    dotCounter *= 10;
    time /= 100;
    for(int i = 1; i <= ghostCounter; i++){
        score += i * 100;
    }
    score += dotCounter;
    score /= time;
    return score;
}

#endif

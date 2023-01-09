#ifndef STRUCTS_H 
#define STRUCTS_H

#include <iostream>

using namespace std;

struct Coords
{
    int i;
    int j;
    bool isThereWall(int **arr, Coords coords, char direction);
};

/*struct Status
{
    Coords coords;
    int lives;
    char current_direction;
    char input_direction;
    bool isThereWall(int **arr, Coords coords, char direction);
};*/


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

#endif

#ifndef PACMAN_H
#define PACMAN_H

#include <iostream>
#include "structs.h"

using namespace std;

class Pacman{
public:
    Coords coords;
    int lives;
    char current_direction;
    char input_direction;
    Pacman(Coords coords, int lives, char current_direction, char input_direction){
        coords = coords;
        lives = lives;
        current_direction = current_direction;
        input_direction = input_direction;
    }

    void updateDirection(int **arr, Pacman &pacman);
    void move(int **&arr, Pacman &pacman, bool &pacmanCheck);
};

#endif

#ifndef GAME_H
#define GAME_H


#include <iostream>
#include "config.h"
#include "structs.h" 
#include "maze_generator.h"
#include "ghost.h"
#include "pacman.h"
#include "database.h"
#include "consul.h"
#include <conio.h>

class Game{

public:
    void setPlay(int**, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int, int);
    void play(int**, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int, int, sqlite3 *&db, Consul&);
    int ** initializeMatrix(int, int);
    void saveGame(int **&);

    void printMatrix(int **, int, int, bool&, int, long long int);
    void showMenu();

    void clearGhost(int **&, Coords, int, int); //can be deleted
};


#endif
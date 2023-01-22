#ifndef GHOST_H
#define GHOST_H

#include <iostream>
#include "structs.h"
#include <cstdlib>

using namespace std;

class Ghost{

public:
	Coords coords;
	int velocity;
	char direction;
	int previousStatus;
	char mode;  //s for scatter, c for chase and d for deadwalker mode
	void move(int **&ground, int &previousStatus, bool &pacmanCheck);
};

class Blinky: public Ghost{

};



#endif

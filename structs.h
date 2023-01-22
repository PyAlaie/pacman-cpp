#ifndef STRUCTS_H 
#define STRUCTS_H

#include <iostream>
#include <conio.h> 
#include <cmath>
#include <string>

using namespace std;

int dotCounter = 0;
int ghostCounter = 0;       //countds the number of ghosts that had been eaten

struct Coords
{
    int i;
    int j;
};


char getInput(char);
bool isThereWall(int **arr, Coords coords, char direction);
bool pacmanCheck(int **&map, char pacmanDir, char ghostDir);
void coloredCout(string text, string color);


#define ESC "\033["
#define GREEN_TXT "32"
#define RED_TXT "31"
#define YELLOW_TXT "33"
#define RESET "\033[m"
#define BLUE_TXT "36"

void coloredCout(std::string text, std::string color){
    if(color == "green"){
        cout << ESC << ";" << GREEN_TXT <<"m"<< text << RESET;
    }
    else if(color == "red"){
        cout << ESC << ";" << RED_TXT <<"m"<< text << RESET;
    }
    else if(color == "yellow"){
        cout << ESC << ";" << YELLOW_TXT <<"m"<< text << RESET;
    }
    else if(color == "blue"){
        cout << ESC << ";" << BLUE_TXT <<"m"<< text << RESET;
    }
}

char getInput(char current_dir){
    char dir = current_dir;
    if (_kbhit())
    {
        switch (getch())
        {
            case 'a':
                dir = 'a';
                break;
            case 'd':
                dir = 'd';
                break;
            case 'w':
                dir = 'w';
                break;
            case 's':
                dir = 's';
                break;
            case 'p':
            	dir = 'p';
            	break;
        }
    }
    return dir;
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

int calScore(int dotCounter, int ghostCounter){
    int score = 0;
    dotCounter *= 10;
    for(int i = 1; i <= ghostCounter; i++){
        score += i * 100;
    }
    score += dotCounter;
    return score;
}

#endif

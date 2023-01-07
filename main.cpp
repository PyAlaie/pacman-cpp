#include <iostream>
#include <conio.h> 
#include "config.h"
#include "structs.h" 
#include "maze_generator.h"

using namespace std;

int ** initializeMatrix(int n, int m);
void drawBorders(int **&arr, int n, int m);
void printMatrix(int **arr, int n, int m);
char getInput(char current_dir);
void updatePacmanDirection(int **arr, Status &pacman);
bool isThereWall(int **arr, Coords coords, char direction);
void movePacman(int **&arr, Status &pacman);

int main(){
    int n, m;
    cin >> n >> m;

    // creating the matrix
    int **mat = initializeMatrix(n,m);

    // adding pacman (randomly :)) to the middle of the map (as a star :))
    mat[n/2][m/2] = 2; 
    Coords pacmanCoor;
    pacmanCoor.i = n/2;
    pacmanCoor.j = m/2;

    // creating status for pacman
    Status pacman;
    pacman.coords = pacmanCoor;
    pacman.lives = 3;
    pacman.current_direction = 'd';
    pacman.input_direction = 'd';

    while(1){
        pacman.input_direction = getInput(pacman.input_direction);
        updatePacmanDirection(mat,pacman);
        movePacman(mat,pacman);
        system(CLEAR);
        printMatrix(mat,n,m);
        usleep(DELAY_TIME);
    }

    return 0;
}

void movePacman(int **&arr, Status &pacman){
    switch (pacman.current_direction)
    {
    case 'w':
        if(!isThereWall(arr, pacman.coords, 'w')){
            arr[pacman.coords.i][pacman.coords.j] = 0;
            pacman.coords.i--;
            arr[pacman.coords.i][pacman.coords.j] = 2;
        }
        break;
    case 's':
        if(!isThereWall(arr, pacman.coords, 's')){
            arr[pacman.coords.i][pacman.coords.j] = 0;
            pacman.coords.i++;
            arr[pacman.coords.i][pacman.coords.j] = 2;
        }
        break;
    case 'd':
        if(!isThereWall(arr, pacman.coords, 'd')){
            arr[pacman.coords.i][pacman.coords.j] = 0;
            pacman.coords.j++;
            arr[pacman.coords.i][pacman.coords.j] = 2;
        }
        break;
    case 'a':
        if(!isThereWall(arr, pacman.coords, 'a')){
            arr[pacman.coords.i][pacman.coords.j] = 0;
            pacman.coords.j--;
            arr[pacman.coords.i][pacman.coords.j] = 2;
        }
        break;
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

void updatePacmanDirection(int **arr, Status &pacman){
    if(!isThereWall(arr,pacman.coords,pacman.input_direction)){
        pacman.current_direction = pacman.input_direction;
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
        }
    }
    return dir;
}

int ** initializeMatrix(int n, int m){
    //creating the matrix
    int ** new_arr = new int*[29];
    for (int i = 0; i < 29; ++i) {
        new_arr[i] = new int[28];
        for (int j = 0; j < 28; ++j) {
            new_arr[i][j] = 0;
        }
    }

    // drawMaze(new_arr,n,m);
    drawSimpleMaze(new_arr,n,m);
    drawBorders(new_arr, n,m);  
    printMatrix(new_arr, n,m);

    return new_arr;
}

void drawBorders(int **&arr, int n, int m){
    // in the matrix, 1 represents wall block, while 0 represents path
    // this function turns every number on the border of the matrix to 1
    for(int i = 0; i < n; i++){
        arr[i][0] = 1;
        arr[i][m-1] = 1;
    }
    for(int j = 0; j < m; j++){
        arr[0][j] = 1;
        arr[n-1][j] = 1;
    }
}

void printMatrix(int **arr, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j<m;j++){
            switch (arr[i][j])
            {
            case 0:
                // path
                cout<<" ";
                break;
            case 1:
                // wall
                cout<<"#";
                break;
            case 2:
                // pacman
                cout<<"*";
                break;
            case -1:
                // condidate
                cout<<"o";
                break;
            }
        }
        cout<<endl;
    }
}
#ifndef MAZE_GENERATOR_GOD_MODE_H
#define MAZE_GENERATOR_GOD_MODE_H
#include <iostream>
#include <cstdlib>
#include "structs.h"
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;

void drawBorders(int **&arr, int n, int m);
void drawGodMaze(int **&arr, int n, int m);
void updateStartingPositions(int **&arr, int n, int m, int margin, vector<Coords> &startingPoints);
bool checkNxNIsEmplty(int **arr, int i, int j, int n);
void drawNxNWall(int **&arr, int i, int j, int n);
Coords chooseRandomStartingPoint(vector<Coords> startingPoints);
void printMatrix(int **arr, int n, int m);
void drawBorders(int **&arr, int n, int m);
void expandWall(int **&arr, int n, int m, Coords point);
bool removeDeadends(int **&arr, int n, int m);
vector<char> deadends(int **arr, int i, int j);
void expandPoint(int **&arr, int n, int m, Coords point);
void mirrorMaze(int **&map, int n, int m);
bool isASingleDot(int **arr, int n, int m, int i, int j);
bool canExpandToRight(int **arr, int n, int m, int i, int j);
bool canExpandToDown(int **arr, int n, int m, int i, int j);
void drawGhostHouse(int **&arr, int n, int m);
void drawTempLine(int **&arr, int n, int m);
int ** initializeMatrix(int, int);
void drawRandomCherries(int **&arr, int n, int m);
void updateCherryPossiblePoints(int **arr, int n, int m, vector<Coords> &points);

void updateCherryPossiblePoints(int **arr, int n, int m, vector<Coords> &points){
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] == 0){
                Coords p;
                p.i = i;
                p.j = j;
                points.push_back(p);
            }
        }
    }
}

void drawRandomCherries(int **&arr, int n, int m){
    vector<Coords> points;
    for(int i = 0; i < 4; i++){
        updateCherryPossiblePoints(arr,n,m,points);
        Coords point = chooseRandomStartingPoint(points);
        arr[point.i][point.j] = 3;
        points.clear();
    }
}

void drawTempLine(int **&arr, int n, int m){
    int width = m/2+1;
    if(m % 2 == 1){
        width = m/2+1;
    }
    else{
        // width = m/2;
    }
    for(int i = 0; i < n; i ++){
        arr[i][width] = 1;
    }
}

int height = 4;
int width = 4;
void drawGhostHouse(int **&arr, int n, int m){
    int midWidth = m/2;
    for(int i = n/4; i < (n/4)+ height; i++){
        for(int j = (m/2)-width; j < (m/2)+width; j++){
            arr[i][j] = 1;
            copy(arr,arr+n,arr);
        }
    }
}

void blankGhostHouse(int **&arr, int n, int m){
    int midWidth = m/2;
    for(int i = n/4+1; i < (n/4)+ height-1; i++){
        for(int j = (m/2)-width+1; j < (m/2)+width-1; j++){
            arr[i][j] = -1;
            copy(arr,arr+n,arr);
        }
    }

    //putting the door
    for(int j = midWidth-2; j < midWidth+2; j++){
        arr[n/4][j] = -1;
        copy(arr,arr+n,arr);
    }
}

Coords chooseRandomStartingPoint(vector<Coords> startingPoints){
    srand((unsigned) time(NULL));
    Coords res = startingPoints[rand() % startingPoints.size()];
    return res;
}

bool checkNxNIsEmplty(int **arr, int i, int j, int n){
    for(int di = 0; di < n; di++){
        for(int dj = 0; dj<n; dj++){
            if(arr[i+di][j+dj] != 0){
                return false;
            }
        }
    }
    return true;
}

void drawNxNWall(int **&arr, int i, int j, int n){
    for(int di = 0; di < n; di++){
        for(int dj = 0; dj < n; dj++){
            arr[i+1+di][j+1+dj] = 1;
        }
    }
}

void updateStartingPositions(int **&arr, int n, int m, int margin, vector<Coords> &startingPoints){
    startingPoints.clear();
    // copy(startingPoints.begin(), startingPoints.end(), startingPoints);
    for(int i = 0; i < n-margin; i++){
        for(int j = 0; j < m-margin; j++){
            if(checkNxNIsEmplty(arr, i, j, margin)){
                Coords point;
                point.i = i;
                point.j = j;
                startingPoints.push_back(point);
            }
        }
    }
    // cout<<startingPoints.size()<<endl;
}

void expandWall(int **&arr, int n, int m, Coords point){
    bool upperWall = false, leftWall = false, rightWall = false, downWall = false;

    Coords topLeft = point;
    Coords topRight = {point.i, point.j+3};
    Coords bottomLeft = {point.i+3, point.j};

    int margin = 2;

    if(topLeft.j - margin >= 0){
        for(int di = 0; di < 3; di++){
            if(arr[topLeft.i+di][topLeft.j-margin] == 1 && arr[topLeft.i+di][topLeft.j-1] == 0){
                leftWall = true;
                break;
            }
        }
    }

    if(topRight.j + margin < m){
        for(int di = 0; di < 3; di++){
            if(arr[topRight.i+di][topRight.j+margin] == 1 && arr[topRight.i+di][topRight.j+1] == 0){
                rightWall = true;
                break;
            }
        }
    }

    if(topLeft.i - margin >= 0){
        for(int dj = 0; dj < 3; dj++){
            if(arr[topLeft.i-margin][topLeft.j+dj] == 1 && arr[topLeft.i-1][topLeft.j+dj] == 0){
                upperWall = true;
                break;
            }
        }
    }

    if(bottomLeft.i + margin < n){    
        for(int dj = 0; dj < 3; dj++){
            if(arr[bottomLeft.i+margin][bottomLeft.j+dj] == 1 && arr[bottomLeft.i+1][bottomLeft.j+dj] == 0){
                downWall = true;
                break;
            }
        }
    }

    if(leftWall){
        arr[topLeft.i + 1][topLeft.j] = 1;
        arr[topLeft.i + 2][topLeft.j] = 1;
    }

    if(rightWall){
        arr[topRight.i + 1][topRight.j] = 1;
        arr[topRight.i + 2][topRight.j] = 1;
    }

    if(upperWall){
        arr[topRight.i][topRight.j-1] = 1;
        arr[topRight.i][topRight.j-2] = 1;
    }

    if(downWall){
        arr[bottomLeft.i][bottomLeft.j+1] = 1;
        arr[bottomLeft.i][bottomLeft.j+2] = 1;
    }
}

void expandPoint(int **&arr, int n, int m, Coords point){
    // expand right
    int rightExpand = 1;
    while(true){
        if(canExpandToRight(arr,n,m,point.i, point.j+rightExpand)){
            arr[point.i][point.j+rightExpand] = 1;
            rightExpand++;
        }
        else{
            break;
        }
    }

    // expand down
    int downExapnd = 1;
    while(true){
        if(canExpandToDown(arr,n,m,point.i+downExapnd, point.j)){
            arr[point.i+downExapnd][point.j] = 1;
            downExapnd++;
        }
        else{
            break;
        }
    }
}

void drawGodMaze(int **&arr, int n, int m){
    drawBorders(arr,n,m);
    drawGhostHouse(arr,n,m);
    drawTempLine(arr,n,m);
    vector<Coords> startingPoints; 
    updateStartingPositions(arr,n,m,4,startingPoints);
    while(!startingPoints.empty()){
        Coords start = chooseRandomStartingPoint(startingPoints);

        drawNxNWall(arr, start.i, start.j, 2);

        expandWall(arr,n,m, start);
        
        updateStartingPositions(arr,n,m,4,startingPoints);

        // system("clear");
        // printMatrix(arr,n,m);
        // usleep(50000);
    }

    for(int i = 1; i < n-1; i++){
        for(int j = 1; j < m -1 ; j++){
            Coords start;
            start.i = i;
            start.j = j;
            if(checkNxNIsEmplty(arr, i, j, 3)){
                arr[start.i+1][start.j+1] = 1;
                copy(arr, arr+n, arr);
                // system("clear");
                // printMatrix(arr,n,m);
                // usleep(100000);
                Coords newPoint;
                newPoint.i = start.i +1;
                newPoint.j = start.j +1;
                expandPoint(arr,n,m,newPoint);
                // system("clear");
                // printMatrix(arr,n,m);
                // usleep(100000);
            }
        }
    }

    blankGhostHouse(arr,n,m);
    mirrorMaze(arr,n,m);
    drawRandomCherries(arr,n,m);
    // system("clear");
    // printMatrix(arr,n,m);
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
	int dotCounter;				//if there is no dot in the map, you are the winner!	
	bool flag = 1;				//checks if there is pacman in map
    for(int i = 0; i < n; i++){
        for(int j = 0; j<m;j++){
            switch (arr[i][j])
            {
            case 0:
                // path
                cout<<".";
                dotCounter++;
                break;
            case 1:
                // wall
                cout<<"#";
                break;
            case 2:
                // pacman
                cout<<"*";
                flag = 0;
                break;
            case -1:
                // blank
                cout<<" ";
                break;
            case -2:
            	// ghost
            	cout << "@";
            	break;
            case 3:
            	// cherry
            	cout << "C";
            	break;
            }
        }
        cout<<endl;
    }
}

bool removeDeadends(int **&arr, int n, int m){
    for(int i = 1; i < n -1; i++){
        for(int j = 1; j < m-1; j++){
            if(deadends(arr, i, j).size() == 3 && arr[i][j] == 0){
                vector<char> deadendDirs = deadends(arr,i,j);
                srand((unsigned) time(NULL));
                char dir = deadendDirs[rand()%deadendDirs.size()];
                switch (dir)
                {
                    case 'a':
                        arr[i][j-1] = 0;
                        break;
                    case 'd':
                        arr[i][j+1] = 0;
                        break;
                    case 'w':
                        arr[i-1][j] = 0;
                        break;
                    case 's':
                        arr[i+1][j] = 0;
                        break;
                }
                usleep(50000);
                system("clear");
                printMatrix(arr,n,m);
            }
        }
    }
}

vector<char> deadends(int **arr, int i, int j){
    vector<char> dirs;

    if(arr[i+1][j] == 1) dirs.push_back('s');
    if(arr[i][j+1] == 1) dirs.push_back('d');
    if(arr[i][j-1] == 1) dirs.push_back('a');
    if(arr[i-1][j] == 1) dirs.push_back('w');

    return dirs;
}

void mirrorMaze(int **&map, int n, int m){
    int half = m/2 +1;
    // if( m % 2 ==0){
    //     half = m/2; 
    // }
    for(int i = 0; i < n; i++){
        for(int j = 0; j < half; j++){
            map[i][m-1-j] = map[i][j];
        }
    }
}

bool isASingleDot(int **arr, int n, int m, int i, int j){
    if(i-1 < 0 || i+1 >= n || j-1 < 0 || j + 1 >= m ){
        return false;
    }

    if(arr[i + 1][j] != 0 
    && arr[i - 1][j] != 0 
    && arr[i][j + 1] != 0 
    && arr[i][j - 1] != 0 
    && arr[i - 1][j - 1] != 0 
    && arr[i + 1][j - 1] != 0 
    && arr[i - 1][j + 1] != 0 
    && arr[i + 1][j + 1] != 0
    ){
        return true;
    }
    return false;
}

bool canExpandToRight(int **arr, int n, int m, int i, int j){
    if(arr[i+1][j] == 0
    && arr[i-1][j] == 0
    && arr[i-1][j+1] == 0
    && arr[i+1][j+1] == 0
    && arr[i][j+1] == 0
    ){
        return true;
    }
    return false;
}

bool canExpandToDown(int **arr, int n, int m, int i, int j){
    if(arr[i][j+1] == 0
    && arr[i][j-1] == 0
    && arr[i+1][j-1] == 0
    && arr[i+1][j+1] == 0
    && arr[i+1][j] == 0
    ){
        return true;
    }
    return false;
}

int ** initializeMatrix(int n, int m){
    //creating the matrix
    int ** new_arr = new int*[n];
    for (int i = 0; i < n; ++i) {
        new_arr[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            new_arr[i][j] = 0;
        }
    }

    drawGodMaze(new_arr,n,m);

    
    return new_arr;
}

#endif
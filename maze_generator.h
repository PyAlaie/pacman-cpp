#include <iostream>
#include <cstdlib>
#include "structs.h"
#include <vector>
#include <conio.h>
#include <fstream>

using namespace std;

Coords selectRandomPoint(int n, int m);
void drawMaze(int **&arr, int n, int m);
void updateCondidates(int **&arr, int n, int m, vector<Coords> &condidatePoints);
void drawCondidatesForPoint(int **&arr, int n, int m, vector<Coords> &condidatePoints, Coords point);
void drawPathFromCondidate(int **&arr, int n, int m, Coords condidate);
Coords selectRandomCondidate(vector<Coords> condidatePoints);
void autoCondidateRemove(int **&arr, int n, int m, vector<Coords> &condidatePoints);
bool isTherePathAround(int **arr, Coords point);
void drawSimpleMaze(int **&arr, int n, int m);
void removeDeadends(int **&arr, int n, int m);
vector<char> deadends(int **arr, int i, int j);

Coords selectRandomPoint(int n, int m){
    srand((unsigned) time(NULL));
    Coords res;
    res.i = rand()%(n-2)+1;
    res.j = rand()%(m-2)+1;
    return res;
}

bool isTherePathAround(int **arr, Coords point){
    if(arr[point.i][point.j+1] == 0){
        return true;
    }
    if(arr[point.i][point.j-1] == 0){
        return true;
    }
    if(arr[point.i-1][point.j] == 0){
        return true;
    }
    if(arr[point.i+1][point.j] == 0){
        return true;
    }
    return false;
}

void autoCondidateRemove(int **&arr, int n, int m, vector<Coords> &condidatePoints){
    vector<Coords> res;
    for(int index = 0; index<condidatePoints.size(); index++){
        if(!isTherePathAround(arr,condidatePoints[index])){
            res.push_back(condidatePoints[index]);
        }
        else{
            arr[condidatePoints[index].i][condidatePoints[index].j] = 1;
            copy(arr,arr+n,arr);
        }
    }
    condidatePoints.clear();
    condidatePoints.swap(res);
}

void drawPathFromCondidate(int **&arr, int n, int m, Coords condidate){
    arr[condidate.i][condidate.j] = 0;
    copy(arr, arr+n, arr);
    if(condidate.i + 2 < n){
        if(arr[condidate.i + 2][condidate.j] == 0){
            arr[condidate.i +1][condidate.j] = 0;
            return;
        }
    }
    if(condidate.i - 2 >= 0){
        if(arr[condidate.i - 2][condidate.j] == 0){
            arr[condidate.i-1][condidate.j] = 0;
            return;
        }
    }
    if(condidate.j - 2 >= 0){
        if(arr[condidate.i][condidate.j - 2] == 0){
            arr[condidate.i][condidate.j - 1] = 0;
            return;
        }
    }
    if(condidate.j + 2 < m){
        if(arr[condidate.i][condidate.j + 2] == 0){
            arr[condidate.i][condidate.j + 1] = 0;
            return;
        }
    }
}

Coords selectRandomCondidate(vector<Coords> condidatePoints){
    int index = rand()%condidatePoints.size();
    return condidatePoints[index];
}

void updateCondidates(int **&arr, int n, int m, vector<Coords> &condidatePoints){
    Coords point;
    for(int i = 0; i<n;i++){
        for(int j = 0; j < m; j++){
            if(arr[i][j] == 0){
                point.i = i;
                point.j = j;
                drawCondidatesForPoint(arr,n,m,condidatePoints,point);
            }
        }
    }
}

void drawCondidatesForPoint(int **&arr, int n, int m, vector<Coords> &condidatePoints, Coords point){
    if(point.i - 2 >= 1){
        Coords newPoint = point;
        newPoint.i -= 2;
        if(arr[point.i-2][point.j] == 1){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
    if(point.i + 2 < n-1){
        Coords newPoint = point;
        newPoint.i += 2;
        if(arr[point.i+2][point.j] == 1){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
    if(point.j + 2 < m-1){
        Coords newPoint = point;
        newPoint.j += 2;
        if(arr[point.i][point.j+2] == 1){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
    if(point.j - 2 >= 1){
        Coords newPoint = point;
        newPoint.j -= 2;
        if(arr[point.i][point.j-2] == 1){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
}

void printMatrixx(int **arr, int n, int m){
    for(int i = 0; i < n; i++){
        for(int j = 0; j<m;j++){
            switch (arr[i][j])
            {
            case 0:
                // path
                cout<<".";
                break;
            case 1:
                // wall
                // cout<<"\u2588";
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


void drawMaze(int **&arr, int n, int m){
    Coords startPoint = selectRandomPoint(n,m); 

    arr[startPoint.i][startPoint.j] = 0;
    system("clear");
    vector<Coords> condidatePoints;
    updateCondidates(arr,n,m,condidatePoints);
    // printMatrixx(arr,n,m);

    int c = 0;
    while (!condidatePoints.empty())
    {   
        // usleep(8000);
        // system("clear");
        Coords point = selectRandomCondidate(condidatePoints);

        drawPathFromCondidate(arr,n,m,point);

        for(int i = 0; i < n;i++){
            for(int j = 0; j<m;j++){
                if(arr[i][j] == -1){
                    arr[i][j] = 1;
                }
            }
        }
        condidatePoints.clear();

        updateCondidates(arr,n,m,condidatePoints);
        autoCondidateRemove(arr,n,m,condidatePoints);
        // printMatrixx(arr,n,m);
        c++;
    }
    // removeDeadends(arr,n,m);
    
}

void drawSimpleMaze(int **&arr, int n, int m){
    ifstream File("sample_maze.txt");
    string line;
    int counter = 0;
    while(getline(File,line)){
        for(int j = 0; j<28; j++){
            if(line[j*2] == '1'){
                arr[counter][j] = 1;
            }
        }
        counter ++;
    }
}

void removeDeadends(int **&arr, int n, int m){
    for(int i = 1; i < n -1; i++){
        for(int j = 1; j < m-1; j++){
            if(deadends(arr, i, j).size() == 3){
                arr[i][j] = -1;
                system("clear");
                printMatrixx(arr,n,m);
                usleep(1000000);
                arr[i][j] = 0;
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
                // usleep(500000);
                system("clear");
                printMatrixx(arr,n,m);
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
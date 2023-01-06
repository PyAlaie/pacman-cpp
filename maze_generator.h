#include <iostream>
#include <cstdlib>
#include "structs.h"
#include <vector>
#include <conio.h>

using namespace std;

Coords selectRandomPoint(int n, int m);
void drawMaze(int **&arr, int n, int m);
void updateCondidates(int **&arr, int n, int m, vector<Coords> &condidatePoints);
void drawCondidatesForPoint(int **&arr, int n, int m, vector<Coords> &condidatePoints, Coords point);
void drawPathFromCondidate(int **&arr, int n, int m, Coords condidate);
Coords selectRandomCondidate(vector<Coords> condidatePoints);
vector<Coords> autoCondidateRemove(int **&arr, int n, int m, vector<Coords> condidatePoints);
bool isTherePathAround(int **arr, Coords point);

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

vector<Coords> autoCondidateRemove(int **&arr, int n, int m, vector<Coords> condidatePoints){
    vector<Coords> res;
    for(int index = 0; index<condidatePoints.size(); index++){
        if(!isTherePathAround(arr,condidatePoints[index])){
            res.push_back(condidatePoints[index]);
        }
        else{
            arr[condidatePoints[index].i][condidatePoints[index].j] = 1;
        }
    }
    return res;
}

void drawPathFromCondidate(int **&arr, int n, int m, Coords condidate){
    arr[condidate.i][condidate.j] = 0;
    if(condidate.i + 2 < n){
        if(arr[condidate.i + 2][condidate.j] == 0){
            // arr[condidate.i][condidate.j] = 0;
            arr[condidate.i +1][condidate.j] = 0;
            return;
        }
    }
    if(condidate.i - 2 >= 0){
        if(arr[condidate.i - 2][condidate.j] == 0){
            // arr[condidate.i][condidate.j] = 0;
            arr[condidate.i-1][condidate.j] = 0;
            return;
        }
    }
    if(condidate.j - 2 >= 0){
        if(arr[condidate.i][condidate.j - 2] == 0){
            // arr[condidate.i][condidate.j] = 0;
            arr[condidate.i][condidate.j - 1] = 0;
            return;
        }
    }
    if(condidate.j + 2 < m){
        if(arr[condidate.i][condidate.j + 2] == 0){
            // arr[condidate.i][condidate.j] = 0;
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
        if(arr[point.i-2][point.j] == 1 && !isTherePathAround(arr,newPoint)){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
    if(point.i + 2 < n-1){
        Coords newPoint = point;
        newPoint.i += 2;
        if(arr[point.i+2][point.j] == 1 && !isTherePathAround(arr,newPoint)){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
    if(point.j + 2 < m-1){
        Coords newPoint = point;
        newPoint.j += 2;
        if(arr[point.i][point.j+2] == 1 && !isTherePathAround(arr,newPoint)){
            arr[newPoint.i][newPoint.j] = -1;
            condidatePoints.push_back(newPoint);
        }
    }
    if(point.j - 2 >= 1){
        Coords newPoint = point;
        newPoint.j -= 2;
        if(arr[point.i][point.j-2] == 1 && !isTherePathAround(arr,newPoint)){
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


void drawMaze(int **&arr, int n, int m){
    Coords startPoint = selectRandomPoint(n,m); 
    arr[startPoint.i][startPoint.j] = 0;
    system("clear");
    printMatrixx(arr,n,m);
    vector<Coords> condidatePoints;
    updateCondidates(arr,n,m,condidatePoints);

    int c = 0;
    while (c<1000)
    {   
        usleep(1000000);
        Coords point = selectRandomCondidate(condidatePoints);
        // arr[point.i][point.j] = 0;

        drawPathFromCondidate(arr,n,m,point);
        // condidatePoints.clear();
        condidatePoints = autoCondidateRemove(arr,n,m,condidatePoints);
        updateCondidates(arr,n,m,condidatePoints);
        condidatePoints = autoCondidateRemove(arr,n,m,condidatePoints);
        system("clear");
        printMatrixx(arr,n,m);
        c++;
    }
    
}
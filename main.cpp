#include <iostream>
#include <conio.h> 
#include "config.h"
#include "structs.h" 
#include "maze_generator.h"
#include "ghost.h"
#include "pacman.h"	

using namespace std;

void showMenu();
void setPlay(int**, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int, int);
void Play(int**, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int, int);
int ** initializeMatrix(int, int);
void drawBorders(int **&, int, int);
void printMatrix(int **, int, int, bool&, int);
char getInput(char);
void coloredCout(string text, string color);

int main(){
    int **map;
    
    // creating status for pacman
    Pacman pacman;
    
    //creating ghosts
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    Ghost ghost4;
    
    
    int action;
    int n, m;
    while(true){
    showMenu();
    cin >> action;
	switch(action){
		case 1:
			cout << "Pleace enter the dimensions of the game(x, y): ";
			cin >> n >> m;

			// creating the matrix
			pacman.lives = 3;
			map = initializeMatrix(n,m);
			setPlay(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
			Play(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
			break;
		case 2:
		case 3:
		case 4:
			return 0;
	}
    }

    return 0;
}


void showMenu(){
    system(CLEAR);
    coloredCout("\nWelcome to Pacman's Coconut version, Please choose from the list below\n\n", "green");
    coloredCout("1. New Game\n", "blue");
    coloredCout("2. Load Game\n", "blue");
    coloredCout("3. Ranking\n", "blue");
    coloredCout("4. Exit\n\n", "blue");
    cout<<"-> ";
}

void setPlay(int **map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int n, int m){

    // adding pacman (randomly :)) to the middle of the map (as a star :))
    map[n/2][m/2] = 2; 
    Coords pacmanCoor;
    pacmanCoor.i = 3 * n/4;
    pacmanCoor.j = m/2;
    
    
    // creating status for pacman
    pacman.coords = pacmanCoor;
    pacman.current_direction = 'd';
    pacman.input_direction = 'd';
    
    
    // adding ghosts to some place
    Coords ghost1Coords;
    ghost1Coords.i = n/2;
    ghost1Coords.j = m/2;
    
    Coords ghost2Coords;
    ghost2Coords.i = n/2 + 1;
    ghost2Coords.j = m/2;
    
    Coords ghost3Coords;
    ghost3Coords.i = n/2;
    ghost3Coords.j = m/2 + 1;
    
    Coords ghost4Coords;
    ghost4Coords.i = n/2 + 1;
    ghost4Coords.j = m/2 + 1;
    
    //set ghosts
    ghost1.velocity = 4;
    ghost1.direction = 'w';
    ghost1.coords = ghost1Coords;
    
    ghost2.velocity = 4;
    ghost2.direction = 'w';
    ghost2.coords = ghost2Coords;
    
    ghost3.velocity = 4;
    ghost3.direction = 'w';
    ghost3.coords = ghost3Coords;
    
    ghost4.velocity = 4;
    ghost4.direction = 'w';
    ghost4.coords = ghost4Coords;
    
    ghost1.previousStatus = 0;
   	ghost2.previousStatus = 0;
    ghost3.previousStatus = 0;
   	ghost4.previousStatus = 0;
	
}

void Play(int **map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int n, int m){
   
    int counter = 0;	//claculate the time to release ghosts;`
    
    bool pacmanCheck = 0;		//checks if pacman is alive or not;
    
    cout << "Enter k to start\n";
    char input = 'h';
    while(input != 'k'){
    	cin >> input;
    }
    while(pacman.lives != 0){
    	moveGhost(map, ghost1, ghost1.previousStatus, pacmanCheck);
    	
    	if(counter >= 10){
    		moveGhost(map, ghost2, ghost2.previousStatus, pacmanCheck);
    	}
    	
    	
    	if(counter >= 110){
    		moveGhost(map, ghost3, ghost3.previousStatus, pacmanCheck);
    	}
    	
    	
    	if(counter >= 210){
    		moveGhost(map, ghost3, ghost4.previousStatus, pacmanCheck);
    	}
    	
    	
        pacman.input_direction = getInput(pacman.input_direction);
        updatePacmanDirection(map,pacman);
        movePacman(map,pacman);
        system(CLEAR);
        printMatrix(map,n,m,pacmanCheck,pacman.lives);
        if(pacmanCheck){
        	pacman.lives--;
        	setPlay(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
        	pacmanCheck = 0;
        	counter = 0;
        }
        usleep(DELAY_TIME);
        
        if( counter <= 220){
	        counter++;
		}
    }
    
    cout << "Game Over!\nYour score is \nEnter b to back to menu";
    while(input != 'b'){
    	cin >> input;
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
    bool temp = 0;
    printMatrix(new_arr, n,m,temp,3);

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

void printMatrix(int **arr, int n, int m, bool &pacmanCheck, int lives){   
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
                // condidate
                cout<<" ";
                break;
            case -2:
            	// ghost
            	cout << "@";
            	break;
            }
        }
        if(i == 0){
        	cout << "			LIVES = " << lives << endl;
        }
        else{
	        cout<<endl;
	    }
    }
    
    if(flag || !dotCounter)
    	pacmanCheck = 1;
    else
    	pacmanCheck = 0;
    	
}

#define ESC "\033["
#define GREEN_TXT "32"
#define RED_TXT "31"
#define YELLOW_TXT "33"
#define RESET "\033[m"
#define BLUE_TXT "36"

void coloredCout(string text, string color){
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
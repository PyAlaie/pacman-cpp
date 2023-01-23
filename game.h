#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <conio.h> 
#include "config.h"
#include "structs.h" 
// #include "maze_generator.h"
#include "ghost.h"
#include "pacman.h"	
#include "database.h"

#include "maze_generator_god_mode.h"
using namespace std;

void showMenu();
void setPlay(int**, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int, int);
void Play(int**, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int, int, sqlite3 *&db);
void printMatrix(int **, int, int, bool&, int, long long int);
char getInput(char);
void coloredCout(string text, string color);
void clearGhost(int **&, Coords, int, int);
void clearPacman(int **&, Coords);
void saveGame(int **&);
int ** initializeMatrix(int, int);

int dotCounter = 0;
int ghostCounter = 0;       //countds the number of ghosts that had been eaten

void showMenu(){
    system(CLEAR);
    coloredCout("\nWelcome to Pacman's Coconut version, Please choose from the list below\n\n", "green");
    coloredCout("1. New Game\n", "blue");
    coloredCout("2. Load Game\n", "blue");
    coloredCout("3. Ranking\n", "blue");
    coloredCout("4. Exit\n\n", "blue");
    std::cout<<"-> ";
}
void setPlay(int **map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int n, int m){

    // adding pacman (randomly :)) to the middle of the map (as a star :))
    map[3*n/4][m/2] = 2; 
    Coords pacmanCoor;
    pacmanCoor.i = 3 * n/4;
    pacmanCoor.j = m/2;
    
    
    // creating status for pacman
    pacman.coords = pacmanCoor;
    pacman.current_direction = 'd';
    pacman.input_direction = 'd';
    
    
    // adding ghosts to some place
    Coords ghost1Coords;
    ghost1Coords.i = n/4+1;
    ghost1Coords.j = m/2;
    
    Coords ghost2Coords;
    ghost2Coords.i = n/4 + 1;
    ghost2Coords.j = m/2;
    
    Coords ghost3Coords;
    ghost3Coords.i = n/4;
    ghost3Coords.j = m/2 + 1;
    
    Coords ghost4Coords;
    ghost4Coords.i = n/4 + 1;
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
    
   ghost1.previousStatus = -1;
   ghost2.previousStatus = -1;
   ghost3.previousStatus = -1;
   ghost4.previousStatus = -1;
	
}

void Play(int **map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int n, int m, sqlite3 *&db){
   
    int counter = 0;	//claculate the time to release ghosts;`
    
    
    long long int timer = 0;	//claculate the time
    
    bool pacmanCheck = 0;		//checks if pacman is alive or not;
    printMatrix(map,n,m,pacmanCheck,pacman.lives,timer);
    std::cout << "Enter k to start\n";
    char input = 't';
    while(true){
       	input = getch();
       	if(input == 'k')
       		break;
    }
    while(pacman.lives != 0){
    	//moveGhost(map, ghost1, ghost1.previousStatus, pacmanCheck);
    	
    	if(counter >= 50){
    		moveGhost(map, ghost2, ghost2.previousStatus, pacmanCheck);
    	}
    	
    	
    	if(counter >= 110){
    		moveGhost(map, ghost3, ghost3.previousStatus, pacmanCheck);
    	}
    	
    	if(counter >= 210){
    		moveGhost(map, ghost3, ghost4.previousStatus, pacmanCheck);
    	}
    	
       	pacman.input_direction = getInput(pacman.input_direction);
       	if(pacman.input_direction == 'p'){
        	std::cout << "Do you want to save the game? Press y to save and c to continue\n";
        	input = getch();
        	while(true){
        		input = getch();
        		if(input == 'c' || input == 'y')
        			break;
        	}
            if(input == 'y'){
                string name;
                coloredCout("Enter Name", "green");
                std::cin >> name;
                while(!isNameValid(name)){
                    coloredCout("Invalid name", "red");
                    std::cin >> name;
                }
                saveGameRecord(name, map, n,m,pacman,ghost1,ghost2,ghost3,ghost4);
                break;
            }
        }
        else{
		updatePacmanDirection(map,pacman);
		movePacman(map,pacman,pacmanCheck);
		system(CLEAR);
		printMatrix(map,n,m,pacmanCheck,pacman.lives, timer);
        bool ghost1Check = ghostCheck(pacman.coords, ghost1.coords);
        bool ghost2Check = ghostCheck(pacman.coords, ghost2.coords);
        bool ghost3Check = ghostCheck(pacman.coords, ghost3.coords);
        bool ghost4Check = ghostCheck(pacman.coords, ghost4.coords);
		if(pacmanCheck || ghost1Check || ghost2Check || ghost3Check || ghost4Check){
			pacman.lives--;
			//clear ghosts
			clearGhost(map, ghost1.coords, ghost1.previousStatus, n);	
			clearGhost(map, ghost2.coords, ghost2.previousStatus, n);
			clearGhost(map, ghost3.coords, ghost3.previousStatus, n);
			clearGhost(map, ghost4.coords, ghost4.previousStatus, n);
            clearPacman(map, pacman.coords);

            setPlay(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
			pacmanCheck = 0;
			counter = 0;
		}
		moveGhost(map, ghost1, ghost1.previousStatus, pacmanCheck);
		usleep(DELAY_TIME);
		
		if(counter <= 220){
			counter++;
		}
		
		timer++;
        }
    }
    
    int score = calScore(dotCounter, ghostCounter);
    std::cout << "Game Over!\nYour score is " << score<<endl;
    string username;
    coloredCout("Enter Name: ", "blue");
    std::cin >> username;
    saveRankingRecord(db, username, score, timer);
    return;
    // while(true){
    //    	input = getch();
    //    	if(input == 'b')
    //    		break;
    // }
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

void printMatrix(int **arr, int n, int m, bool &pacmanCheck, int lives, long long int timer){   
	dotCounter = 0;				//if there is no dot in the map, you are the winner!	
	bool flag = 1;				//checks if there is pacman in map
    for(int i = 0; i < n; i++){
        for(int j = 0; j<m;j++){
            switch (arr[i][j])
            {
            case 0:
                // path
                std::cout<<".";
                dotCounter++;
                break;
            case 1:
                // wall
                std::cout<<"#";
                break;
            case 2:
                // pacman
                if(!pacmanCheck){
                	std::cout<<"*";
                }
                flag = 0;
                break;
            case -1:
                // condidate
                std::cout<<" ";
                break;
            case -2:
            	// ghost
            	std::cout << "@";
            	break;
            }
        }
        if(i == 0){
        	std::cout << "			TIME: " << timer << endl;
        }
        else if(i == 1){
        	std::cout << "			LIVES: " << lives << endl;
        }
        else if(i == 2){
        	std::cout << "			Whenever wnated to stop or save the game enter p" << endl;
        }
        else{
	        std::cout<<endl;
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
        std::cout << ESC << ";" << GREEN_TXT <<"m"<< text << RESET;
    }
    else if(color == "red"){
        std::cout << ESC << ";" << RED_TXT <<"m"<< text << RESET;
    }
    else if(color == "yellow"){
        std::cout << ESC << ";" << YELLOW_TXT <<"m"<< text << RESET;
    }
    else if(color == "blue"){
        std::cout << ESC << ";" << BLUE_TXT <<"m"<< text << RESET;
    }
}
void clearGhost(int **&map, Coords ghostCoords, int previousStatus, int n){
	map[ghostCoords.i][ghostCoords.j] = previousStatus;
	copy(map, map + n, map);
}

void clearPacman(int **&map, Coords pacmanCoords){
    map[pacmanCoords.i][pacmanCoords.j] = 0;
}

#endif
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
void printMatrix(int **, int, int, bool&, int, long long int, Coords, Coords, Coords, Coords, char);
char getInput(char);
void coloredCout(string text, string color);
void clearGhost(int **&, Coords, int, int);
void clearPacman(int **&, Coords);
void saveGame(int **&);
int ** initializeMatrix(int, int);
void loadGame(int**&, Pacman&, Ghost&, Ghost&, Ghost&, Ghost&, int&, int&, mapData);

int dotCounter = 0;
int ghostCounter = 0;       //countds the number of ghosts that had been eaten
bool cherryCheck = 0;
int cherryTime = 0;
int cherryCounter = 0;
// int cherryCheck = 0;
int scatterTime = 0;
int chaseTime = 0;

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
    ghost1Coords.j = m/2 - 2;
    
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

   ghost1.mode = 's';
   ghost2.mode = 's';
   ghost3.mode = 's';
   ghost4.mode = 's';


   ghost2.targetPoint = pacman.coords;

   setTime(scatterTime, chaseTime, 1);

   ghost1.targetPoint. i = n - 2;
   ghost1.targetPoint.j = m - 2;

   ghost1.targetPoint = chooseTargetPoint(ghost1,1,pacman.coords,n,m,pacman.current_direction,ghost1.coords,ghost2.coords);
   changePath(map, ghost1.targetPoint, ghost1.coords, ghost1.path);
   cout << "ghost111: " << ghost1.targetPoint.i << "        " << ghost1.targetPoint.j << endl;

   ghost2.targetPoint. i = 2;
   ghost2.targetPoint.j = m - 2;


	
}

void Play(int **map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int n, int m, sqlite3 *&db){
   
    int counter = 0;	//claculate the time to release ghosts;`
    
    
    long long int timer = 0;	//claculate the time
    
    bool pacmanCheck = 0;		//checks if pacman is alive or not;

    int scatterTimeCalculator = 0;
    int chaseTimeCalculator = 0;
    int cherryTimeCalculator = 0;
    bool flagCherry = 0;

    printMatrix(map,n,m,pacmanCheck,pacman.lives,timer, ghost1.coords, ghost2.coords, ghost3.coords, ghost4.coords, 's');
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
            updateGhostDirection(map, ghost2);
            move(map, ghost2);
    		// moveGhost(map, ghost2, ghost2.previousStatus, pacmanCheck);
    	}
    	if(counter >= 10){
            updateGhostDirection(map, ghost3);
            move(map, ghost3);
    		// moveGhost(map, ghost3, ghost3.previousStatus, pacmanCheck);
    	}
    	if(counter >= 150){
            updateGhostDirection(map, ghost4);
            move(map, ghost4);
    		// moveGhost(map, ghost4, ghost4.previousStatus, pacmanCheck);
    	}
    	
       	pacman.input_direction = getInput(pacman.input_direction);

       	if(pacman.input_direction == 'p'){
        	cout << "Y to save the game, C to continue, E to exit without saving\n";
        	while(true){
        		input = getch();
        		if(input == 'c' || input == 'y' || input == 'e')
        			break;
        	}
            if(input == 'y'){
                string name;
                coloredCout("Enter Name Of Your Game: ", "green");
                cin >> name;
                while(!isNameValid(name)){
                    coloredCout("Invalid name", "red");
                    std::cin >> name;
                }
                saveGameRecord(name, map, n,m,pacman,ghost1,ghost2,ghost3,ghost4);
                break;
            } else if(input == 'c'){
                break;
            }
            else if (input == 'c')
            {
                pacman.input_direction = pacman.current_direction;
            }
            else if (input == 'e')
            {
                break;
            }
        }
        else{
		updatePacmanDirection(map,pacman);
		movePacman(map,pacman,pacmanCheck, cherryCheck, cherryTime);
		system(CLEAR);
        
        
        if(cherryCheck){
            if(!flagCherry){
                cherryCounter++;
            }
            flagCherry = 1;
            cherryTime--;
        }
		printMatrix(map,n,m,pacmanCheck,pacman.lives, timer, ghost1.coords, ghost2.coords, ghost3.coords, ghost4.coords, ghost1.mode);
        bool ghost1Check = ghostCheck(pacman.coords, ghost1.coords);
        bool ghost2Check = ghostCheck(pacman.coords, ghost2.coords);
        bool ghost3Check = ghostCheck(pacman.coords, ghost3.coords);
        bool ghost4Check = ghostCheck(pacman.coords, ghost4.coords);
		if((pacmanCheck || ghost1Check || ghost2Check || ghost3Check || ghost4Check) && !cherryCheck){
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
        else if(cherryCheck){ 
            ghostCounter++;
            if(ghost1Check){
                ghost1.coords.i = n/4 + 1;
                ghost1.coords.j = m/2;
            }
            if(ghost2Check){
                ghost2.coords.i = n/4 + 1;
                ghost2.coords.j = m/2;
            }
            if(ghost3Check){
                ghost3.coords.i = n/4 + 1;
                ghost3.coords.j = m/2;
            }
            if(ghost4Check){
                ghost4.coords.i = n/4 + 1;
                ghost4.coords.j = m/2;
            }
        }
		


        if(scatterTime != scatterTimeCalculator && ghost1.mode == 's'){
            scatterTimeCalculator++;
            chaseTimeCalculator = 0;
        }
        else{
            scatterTimeCalculator = 0;
            ghost1.mode = 'c';
            ghost2.mode = 'c';
            ghost3.mode = 'c';
            ghost4.mode = 'c';
        }

        if(chaseTime != chaseTimeCalculator && ghost1.mode == 'c'){
            chaseTimeCalculator++;
            scatterTimeCalculator = 0;
        }
        else{
            chaseTimeCalculator = 0;
            ghost1.mode = 's';
            ghost2.mode = 's';
            ghost3.mode = 's';
            ghost4.mode = 's';
        }

        // if(abs(ghost1.targetPoint.i - ghost1.coords.i) < 2 && abs(ghost1.targetPoint.j - ghost1.coords.j) < 2){
        //     chooseTargetPoint(ghost1, 1, pacman.coords, n, m, pacman.current_direction, ghost1.coords, ghost2.targetPoint);
        // }
        // chooseTargetPoint(ghost2, 2, pacman.coords, n, m, pacman.current_direction, ghost1.coords, ghost2.targetPoint);
        // chooseTargetPoint(ghost3, 3, pacman.coords, n, m, pacman.current_direction, ghost1.coords, ghost2.targetPoint);
        // chooseTargetPoint(ghost4, 4, pacman.coords, n, m, pacman.current_direction, ghost1.coords, ghost2.targetPoint);

        // ghost1.direction = chooseDirection(map, ghost1.targetPoint, ghost1.coords, ghost1.direction);
        // ghost2.direction = chooseDirection(map, ghost2.targetPoint, ghost2.coords, ghost2.direction);

        Coords temp = chooseTargetPoint(ghost1, 1, pacman.coords, n, m, pacman.current_direction, ghost1.coords, ghost2.coords);
        if(ghost1.targetPoint.i != temp.i && ghost1.targetPoint.j != temp.j){
            ghost1.targetPoint = temp;
            changePath(map, ghost1.targetPoint, ghost1.coords, ghost1.path);
        }
        ghost1.direction = findDirection(ghost1.coords, ghost1.path[ghost1.coords]);
        move(map, ghost1);

        // updateGhostDirection(map, ghost1);
        // move(map, ghost1);

        updateGhostDirection(map, ghost2);
        move(map, ghost2);

        updateGhostDirection(map, ghost3);
        move(map, ghost3);

        updateGhostDirection(map, ghost4);
        move(map, ghost4);
		//moveGhost(map, ghost1, ghost1.previousStatus, pacmanCheck);
		
        
        usleep(DELAY_TIME);
		
		if(counter <= 220){
			counter++;
		}
		if(cherryTime == 0){
            cherryCheck = 0;
            flagCherry = 0;
        }
		timer++;
        }
    }
    
    int score = calScore(dotCounter, ghostCounter, cherryCounter);
    cout << "Game Over!\nYour score is " << score<<endl;
    string username;
    coloredCout("Enter Name: ", "blue");
    std::cin >> username;
    saveRankingRecord(db, username, score, timer);
    return;
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

void printMatrix(int **arr, int n, int m, bool &pacmanCheck, int lives, long long int timer, 
                Coords ghost1, Coords ghost2, Coords ghost3, Coords ghost4, char ghostMode){   
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
                if(cherryCheck)
                    cout << "@";
            	else if(i == ghost1.i && j == ghost1.j)
                    coloredCout("@", "red");
                else if(i == ghost2.i && j == ghost2.j)
                    coloredCout("@", "green");
                else if(i == ghost3.i && j == ghost3.j)
                    coloredCout("@", "blue");
                else if(i == ghost4.i && j == ghost4.j)
                    coloredCout("@", "yellow");
            	//std::cout << "@";
            	break;
            case 3:
                cout << "c";
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
        else if(i == 3){
            std::cout << "          mode: " << ghostMode << endl;
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

void loadGame(int **&map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int &n, int &m, mapData gameToLoad){
    cout<<"mamamia";

    n = gameToLoad.n;
    m = gameToLoad.m;

    map = new int*[n];
    for (int i = 0; i < n; ++i) {
        map[i] = new int[m];
        for (int j = 0; j < m; ++j) {
            map[i][j] = 0;
        }
    }

    copy(gameToLoad.map, gameToLoad.map + gameToLoad.n, map);
    
    // adding pacman to the map according to the loaded game
    // map[gameToLoad.pacman.coords.i][gameToLoad.pacman.coords.j] = 2; 
    Coords pacmanCoor;
    pacmanCoor.i = gameToLoad.pacman.coords.i;
    pacmanCoor.j = gameToLoad.pacman.coords.j;
    
    
    // setting the status for pacman
    pacman.coords = gameToLoad.pacman.coords;
    pacman.current_direction = gameToLoad.pacman.current_direction;
    pacman.input_direction = gameToLoad.pacman.input_direction;
    pacman.lives = gameToLoad.pacman.lives;
    
    
    // adding ghosts to some place
    Coords ghost1Coords;
    ghost1Coords.i = gameToLoad.g1.coords.i;
    ghost1Coords.j = gameToLoad.g1.coords.j;
    
    Coords ghost2Coords;
    ghost2Coords.i = gameToLoad.g2.coords.i;
    ghost2Coords.j = gameToLoad.g2.coords.j;
    
    Coords ghost3Coords;
    ghost3Coords.i = gameToLoad.g3.coords.i;
    ghost3Coords.j = gameToLoad.g3.coords.j;
    
    Coords ghost4Coords;
    ghost4Coords.i = gameToLoad.g4.coords.i;
    ghost4Coords.j = gameToLoad.g4.coords.j;
    
    //set ghosts
    ghost1.velocity = gameToLoad.g1.velocity;
    ghost1.direction = gameToLoad.g1.direction;
    ghost1.coords = gameToLoad.g1.coords;
    
    ghost2.velocity = gameToLoad.g2.velocity;
    ghost2.direction = gameToLoad.g2.direction;
    ghost2.coords = gameToLoad.g2.coords;
    
    ghost3.velocity = gameToLoad.g3.velocity;
    ghost3.direction = gameToLoad.g3.direction;
    ghost3.coords = gameToLoad.g3.coords;
    
    ghost4.velocity = gameToLoad.g4.velocity;
    ghost4.direction = gameToLoad.g4.direction;
    ghost4.coords = gameToLoad.g4.coords;
    
    ghost1.previousStatus = gameToLoad.g1.previousStatus;
    ghost2.previousStatus = gameToLoad.g2.previousStatus;
    ghost3.previousStatus = gameToLoad.g3.previousStatus;
    ghost4.previousStatus = gameToLoad.g4.previousStatus;
}

#endif
#include <iostream>
#include "game.h"


#include <iostream>
#include "config.h"
#include "structs.h" 
#include "maze_generator.h"
#include "ghost.h"
#include "pacman.h"
#include "database.h"
#include "consul.h"

using namespace std;


void 
Game::setPlay(int **map, Pacman &pacman, Ghost &ghost1, Ghost &ghost2, Ghost &ghost3, Ghost &ghost4, int n, int m){

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

void 
Game::play(int **map, Pacman &pacman, Ghost &ghost1,
            Ghost &ghost2, Ghost &ghost3, Ghost &ghost4,
            int n, int m, sqlite3 *&db, Consul &consul){
   
    int counter = 0;	//claculate the time to release ghosts;`
    
    
    long long int timer = 0;	//claculate the time
    
    bool pacmanCheck = 0;		//checks if pacman is alive or not;
    printMatrix(map,n,m,pacmanCheck,pacman.lives,timer);
    cout << "Enter k to start\n";
    char input = 't';
    while(true){
       	input = getch();
       	if(input == 'k')
       		break;
    }
    while(pacman.lives != 0){
    	//moveGhost(map, ghost1, ghost1.previousStatus, pacmanCheck);
    	
    	if(counter >= 50){
    	//	moveGhost(map, ghost2, ghost2.previousStatus, pacmanCheck);
    	}
    	
    	
    	if(counter >= 110){
    	//	moveGhost(map, ghost3, ghost3.previousStatus, pacmanCheck);
    	}
    	
    	if(counter >= 210){
    	//	moveGhost(map, ghost3, ghost4.previousStatus, pacmanCheck);
    	}
    	
       	pacman.input_direction = getInput(pacman.input_direction);
       	if(pacman.input_direction == 'p'){
        	cout << "Do you want to save the game? Press y to save and c to continue\n";
        	input = getch();
        	while(true){
        		input = getch();
        		if(input == 'c' || input == 'y')
        			break;
        	}
            if(input == 'y'){
                string name;
                coloredCout("Enter Name", "green");
                cin >> name;
                while(!isNameValid(name)){
                    coloredCout("Invalid name", "red");
                    cin >> name;
                }
                saveGameRecord(name, map, n,m,pacman,ghost1,ghost2,ghost3,ghost4);
                break;
            }
        }
        else{
		pacman.updateDirection(map,pacman);
		pacman.move(map,pacman,pacmanCheck);
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
            map[pacman.coords.i][pacman.coords.j] = 0;

            setPlay(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
			pacmanCheck = 0;
			counter = 0;
		}
		//moveGhost(map, ghost1, ghost1.previousStatus, pacmanCheck);
		usleep(DELAY_TIME);
		
		if(counter <= 220){
			counter++;
		}
		
		timer++;
        }
    }
    
    int score = calScore(dotCounter, ghostCounter);
    cout << "Game Over!\nYour score is " << score<<endl;
    string username;
    coloredCout("Enter Name: ", "blue");
    cin >> username;
    saveRankingRecord(db, username, score, timer);
    return;
    // while(true){
    //    	input = getch();
    //    	if(input == 'b')
    //    		break;
    // }
}



void 
Game::clearGhost(int **&map, Coords ghostCoords, int previousStatus, int n){
	map[ghostCoords.i][ghostCoords.j] = previousStatus;
}



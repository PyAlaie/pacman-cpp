#include <iostream>
#include "consul.h"
#include "structs.h"
#include "config.h"

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif

#define ESC "\033["
#define GREEN_TXT "32"
#define RED_TXT "31"
#define YELLOW_TXT "33"
#define RESET "\033[m"
#define BLUE_TXT "36"

void 
Consul::showMenu(){
    system(CLEAR);
    coloredCout("\nWelcome to Pacman's Coconut version, Please choose from the list below\n\n", "green");
    coloredCout("1. New Game\n", "blue");
    coloredCout("2. Load Game\n", "blue");
    coloredCout("3. Ranking\n", "blue");
    coloredCout("4. Exit\n\n", "blue");
    cout<<"-> ";
}

void 
Consul::printMatrix(int **arr, int n, int m, bool &pacmanCheck, int lives, long long int timer){   
	dotCounter = 0;				//if there is no dot in the map, you are the winner!	
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
                if(!pacmanCheck){
                	cout<<"*";
                }
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
        	cout << "			TIME: " << timer << endl;
        }
        else if(i == 1){
        	cout << "			LIVES: " << lives << endl;
        }
        else if(i == 2){
        	cout << "			Whenever wnated to stop or save the game enter p" << endl;
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

void 
Consul::coloredCout(string text, string color){
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




#include <iostream>
#include <conio.h> 
#include "game.h"

using namespace std;


int main(){
    int **map;

    // printing the splash screen
    system(CLEAR);
    typeEffect("\nWelcome to Kokonut Pacman!\n", "green");
    usleep(700000);

    // initializing database object
    sqlite3 *db;
    initializeDB(db);

    // creating pacman and ghost objects
    Pacman pacman;
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    Ghost ghost4;
    
    int action;
    int n, m;

    while(true){
    showMenu();

    cin >> action;

    vector<ranking> rr; // to get rankings
    vector<string> savedGames; // to get saved games name
    mapData gameToLoad; // in case of loading a game ... 

	switch(action){
		case 1:
			cout << "Pleace enter the dimensions of the game(x, y): ";
			cin >> n >> m;
            system(CLEAR);

            if(m % 2 == 0){
                m++; // for that mirror thing ... :)
            }

			// creating the matrix
			map = initializeMatrix(n,m);
	        pacman.lives = 3;

			setPlay(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
			Play(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m, db);
			break;
		case 2:
            getSavedGames(savedGames);
            for(int i = 0; i< savedGames.size(); i++){
                if (!(savedGames[i] == ".." || savedGames[i] == ".")){
                    cout<<i<<". "<<savedGames[i]<<endl;
                }
            }
            coloredCout("\nEnter The Index Of Game You Want To Load: ", "blue");

            int a;
            cin >> a;
            system(CLEAR);

            readGameData(savedGames[a], gameToLoad); 
            loadGame(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m, gameToLoad);
            Play(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m, db);

            break;
		case 3:
            rr = getTopScores(db,10);
            for(int i = 0; i< rr.size(); i++){
                cout<<i+1<<". ";
                coloredCout(rr[i].username, "yellow");
                cout<<"\t\t";
                coloredCout(to_string(rr[i].score), "green");
                cout<<endl;
            }

            char b;
            cin>>b;
            break;
		case 4:
			return 0;
            break;
        default:
            break;
	}
    }

    return 0;
}
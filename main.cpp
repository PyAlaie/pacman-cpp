#include <iostream>
#include <conio.h> 
#include "game.h"

using namespace std;


int main(){
    int **map;


    sqlite3 *db;
    initializeDB(db);

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

    vector<ranking> rr; // to get rankings
    vector<string> savedGames; // to get saved games name
    mapData gameToLoad; // in case of loading a game ... 

	switch(action){
		case 1:
			cout << "Pleace enter the dimensions of the game(x, y): ";
			cin >> n >> m;

			// creating the matrix
			pacman.lives = 3;
			map = initializeMatrix(n,m);
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

            readGameData(savedGames[a], gameToLoad); 
            loadGame(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m, gameToLoad);
            Play(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m, db);

            break;
		case 3:
            rr = getTopScores(db,10);
            for(int i = 0; i< rr.size(); i++){
                cout<<rr[i].username<<" "<<rr[i].score<<endl;
            }
           
            break;
		case 4:
			return 0;
            break;
	}
    }

    return 0;
}
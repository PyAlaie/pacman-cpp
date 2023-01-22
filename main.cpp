#include <iostream>
#include <conio.h> 
#include "game.h"
#include "pacman.h"
#include "ghost.h"
#include "maze_generator.h"
#include <vector>

using namespace std;

int main(){
    int **map;


    sqlite3 *db;
    initializeDB(db);

    Coords sample;
    sample.i = 29;
    sample.j = 28;

    Pacman pacman = Pacman(sample, 3, 'd', 'd');
    Consul consul;
    Game game;
    
    //creating ghosts
    Ghost ghost1;
    Ghost ghost2;
    Ghost ghost3;
    Ghost ghost4;
    
    
    int action;
    int n, m;
    while(true){
    consul.showMenu();
    cin >> action;
    vector<ranking> rr;

	switch(action){
		case 1:
			cout << "Pleace enter the dimensions of the game(x, y): ";
			cin >> n >> m;

			// creating the matrix
			map = initializeMatrix(n,m);
			game.setPlay(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m);
			game.play(map, pacman, ghost1, ghost2, ghost3, ghost4, n, m, db, consul);
			break;
		case 2:
            break;
		case 3:
            rr = getTopScores(db,10);
            for(int i = 0; i< rr.size(); i++){
                cout<<rr[i].username<<" "<<rr[i].score<<endl;
            }
            char a;
            cin>>a;
            break;
		case 4:
            break;
			// return 0;
	}
    }

    return 0;
}
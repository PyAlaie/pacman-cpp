#ifndef DATABASE_H 
#define DATABASE_H

#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>
#include "structs.h"
#include "pacman.h"
#include "ghost.h"
#include <fstream>
#include <sstream>
#include <dirent.h>

using namespace std;

struct ranking
{
    string username;
    int score;
};

struct mapData
{
    string name;
    int **map;
    int n;
    int m;
    Pacman pacman;
    Ghost g1;
    Ghost g2;
    Ghost g3;
    Ghost g4;
};

bool initializeDB(sqlite3 *&db);
bool closeDB(sqlite3 *&db);
void saveRankingRecord(sqlite3 *&db,string username, int score);
int createTableRankingIfNotExist(sqlite3 *&db);
vector<ranking> getTopScores(sqlite3 *db, int count);

bool initializeDB(sqlite3 *&db){
    int exit = 0;

    exit = sqlite3_open("database.sqlite3", &db);
    createTableRankingIfNotExist(db);

    return !exit;
}

bool closeDB(sqlite3 *&db){
    int exit = sqlite3_close(db);
    return !exit;
}

void saveRankingRecord(sqlite3 *&db,string username, int score, int time){
    string q = "INSERT INTO RANKING (username, score, time) VALUES (\""+ username + "\", "+to_string(score)+","+to_string(time)+")";
    char* messaggeError;
    int exit = sqlite3_exec(db, q.c_str(), NULL, 0 , &messaggeError);
}

int createTableRankingIfNotExist(sqlite3 *&db){
    string query = "CREATE TABLE IF NOT EXISTS RANKING (username varchar, score int, time int);";
    char* messaggeError;
    int exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messaggeError);
    return exit;
}

vector<ranking> res = {}; 
int counter = 0;
int callback(void *NotUsed, int argc, char **argv, char **azColName){
    ranking r;
    r.username = argv[0];
    r.score = stoi(argv[1]);
    res.push_back(r);
    counter++;
    return 0;
}
  
vector<ranking> getTopScores(sqlite3 *db, int count){
    // returns a vector of ranking structs of top {count} scores from database
    string q = "SELECT * FROM RANKING ORDER BY score DESC LIMIT " + to_string(count);
    char* messaggeError;
    int exit = sqlite3_exec(db, q.c_str(), callback, 0, &messaggeError);
    return res;
}

void saveGameRecord(string name, int **map, int n, int m, Pacman pacman, Ghost g1, Ghost g2, Ghost g3, Ghost g4){
    ofstream File("saved_games/" + name);
    File<<n<<endl<<m<<endl;
    for(int i = 0; i<n; i++){
        for(int j = 0; j < m; j++){
            File<<map[i][j]<<" ";
        }
        File<<endl;
    }
    File<<pacman.coords.i<<","<<pacman.coords.j<<","<<pacman.lives<<","<<pacman.input_direction<<","<<pacman.current_direction<<endl;
    File<<g1.coords.i<<","<<g1.coords.j<<","<<g1.velocity<<","<<g1.direction<<","<<g1.previousStatus<<endl;
    File<<g2.coords.i<<","<<g2.coords.j<<","<<g2.velocity<<","<<g2.direction<<","<<g2.previousStatus<<endl;
    File<<g3.coords.i<<","<<g3.coords.j<<","<<g3.velocity<<","<<g3.direction<<","<<g3.previousStatus<<endl;
    File<<g4.coords.i<<","<<g4.coords.j<<","<<g4.velocity<<","<<g4.direction<<","<<g4.previousStatus<<endl;

    File.close();
}

void readGameData(string name, mapData &data){
    ifstream File("saved_games/" + name);
    string line;

    // getting n and m
    getline(File,line);
    data.n = stoi(line);
    getline(File,line);
    data.m = stoi(line);

    // geting the matrix
    data.map = new int*[data.n];
    for (int i = 0; i < data.n; ++i) {
        data.map[i] = new int[data.m];
        for (int j = 0; j < data.m; ++j) {
            data.map[i][j] = 0;
        }
    }
    for(int i = 0; i < data.n; i++){
        getline(File,line);

        string delimiter = " ";
        string token;

        stringstream ss(line);
        int j = 0;
        while (getline(ss, token, delimiter[0])) {
            data.map[i][j] = stoi(token); 
            j++;
        }
    }

    // getting pacman data
    getline(File,line);

    string delimiter = ",";
    vector<std::string> tokens;
    string token;
    stringstream ss(line);

    while (getline(ss, token, delimiter[0])) {
        tokens.push_back(token);
    }

    data.pacman.coords.i = stoi(tokens[0]);
    data.pacman.coords.j = stoi(tokens[1]);
    data.pacman.lives = stoi(tokens[2]);
    data.pacman.input_direction = tokens[3][0];
    data.pacman.current_direction = tokens[4][0];

    // getting ghost1 data
    getline(File,line);

    tokens.clear();
    stringstream s1(line);

    while (getline(s1, token, delimiter[0])) {
        tokens.push_back(token);
    }

    data.g1.coords.i = stoi(tokens[0]);
    data.g1.coords.j = stoi(tokens[1]);
    data.g1.velocity = stoi(tokens[2]);
    data.g1.direction = tokens[3][0];
    data.g1.previousStatus = stoi(tokens[4]);

    // getting ghost2 data
    getline(File,line);

    tokens.clear();
    stringstream s2(line);

    while (getline(s2, token, delimiter[0])) {
        tokens.push_back(token);
    }

    data.g2.coords.i = stoi(tokens[0]);
    data.g2.coords.j = stoi(tokens[1]);
    data.g2.velocity = stoi(tokens[2]);
    data.g2.direction = tokens[3][0];
    data.g2.previousStatus = stoi(tokens[4]);

    // getting ghost3 data
    getline(File,line);

    tokens.clear();
    stringstream s3(line);

    while (getline(s3, token, delimiter[0])) {
        tokens.push_back(token);
    }

    data.g3.coords.i = stoi(tokens[0]);
    data.g3.coords.j = stoi(tokens[1]);
    data.g3.velocity = stoi(tokens[2]);
    data.g3.direction = tokens[3][0];
    data.g3.previousStatus = stoi(tokens[4]);

    // getting ghost4 data
    getline(File,line);

    tokens.clear();
    stringstream s4(line);

    while (getline(s4, token, delimiter[0])) {
        tokens.push_back(token);
    }

    data.g4.coords.i = stoi(tokens[0]);
    data.g4.coords.j = stoi(tokens[1]);
    data.g4.velocity = stoi(tokens[2]);
    data.g4.direction = tokens[3][0];
    data.g4.previousStatus = stoi(tokens[4]);

    File.close();
}

void getSavedGames(vector<string> &fileNames){
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir ("saved_games/")) != NULL) {
        while ((ent = readdir (dir)) != NULL) {
            fileNames.push_back(ent->d_name);
        }
        closedir (dir);
    } 
    else {
        perror ("");
    }
}

bool isNameValid(string name){
    vector<string> ls;
    getSavedGames(ls);
    for(int i = 0; i<ls.size(); i++){
        if(name == ls[i]){
            return false;
        }
    }
    return true;
}
#endif
#include <iostream>
#include <sqlite3.h>
#include <string>
#include <vector>

using namespace std;

struct ranking
{
    string username;
    int score;
};


bool initializeDB(sqlite3 *&db){
    int exit = 0;

    exit = sqlite3_open("database.sqlite3", &db);
    createTableIfNotExist(db);

    return !exit;
}

bool closeDB(sqlite3 *&db){
    int exit = sqlite3_close(db);
    return !exit;
}

void saveData(sqlite3 *&db,string username, int score){
    string q = "INSERT INTO RANKING (username, score) VALUES (\""+ username + "\", "+to_string(score)+")";
    char* messaggeError;
    int exit = sqlite3_exec(db, q.c_str(), NULL, 0 , &messaggeError);
}

int createTableIfNotExist(sqlite3 *&db){
    string query = "CREATE TABLE IF NOT EXISTS RANKING (username varchar, score int);";
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
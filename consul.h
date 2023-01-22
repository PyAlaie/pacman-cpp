#ifndef CONSUL_H
#define CONSUL_H

#include <iostream>
#include <conio.h>
#include <string>

#define ESC "\033["
#define GREEN_TXT "32"
#define RED_TXT "31"
#define YELLOW_TXT "33"
#define RESET "\033[m"
#define BLUE_TXT "36"

using namespace std;

class Consul{

public:
    void showMenu();
    //void coloredCout(string text, string color);
    void printMatrix(int **, int, int, bool&, int, long long int);
};

#endif
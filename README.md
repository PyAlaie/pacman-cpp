# Pacman-cpp

## Summary

This project is a terminal-based pacman game, written in C++ language, and is developed as final project of C++ programming course.

## Compile and run

In order to run the program, you have to first compile it. The compiler used to write the project is g++ version 7.5.0, so you have to have g++ installed(using other compilers might also work just fine for you, however we recommand using g++, since the project is not tested on other compilers). Also, since it uses SQLite3 database to store ranking data, you have to install the Sqlite3 library as well.

    $ apt install g++ libsqlite3-dev

Then, you have to compile the `main.cpp` file, including the sqlite3 library.

    $ g++ main.cpp -lsqlite3 -o pacman.out

And now the game is ready to run!

    $ ./pacman.out

**NOTE:** The game only runs with out any problems on linux. You might face some problems if you try to run it on windows, including lags and low frame rates.

## Project implementation and features

This implementation of pacman game have gone beyond the classic version of it:

- The game generates a new random maze every time you start a new game. The algorithm used to generate the maze is a c++ implementation of another project that is written in python which you can find [here](https://github.com/shaunlebron/pacman-mazegen).
This algorithm might be a little confusing, so it won't be discussed here, however in case you are intersted, you can check the link above and see how it actually works.

- The ghosts in the game follow you! Unlike the classic pacman, in this version chase you when they are on chase mode(which happens when you have not eaten any cherries). The algorithm that ghosts use to chase you is [BFS or Breadth-first search](https://en.wikipedia.org/wiki/Breadth-first_search).

- The game have this feature that you can save the game you've played so far, and then load it in the future. It also stores ranking data whenever you lose or just quit the game in an SQLite database.

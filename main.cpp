//author: 'Vaishnavi Agarwal'

#include <iostream>
#include "SnakeGame.h"
#include <unistd.h> 

using namespace std;

int main() {
    int level;
    cout << "Choose Level (1: Normal, 2: With Obstacles): ";
    cin >> level;

    SnakeGame game(level);  

    while (!game.isGameOver()) {
        game.draw();
        game.input();
        game.logic();
        usleep(100000); 
    }

    return 0;
}


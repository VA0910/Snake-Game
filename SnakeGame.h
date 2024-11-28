//author: 'Vaishnavi Agarwal'

#ifndef SNAKEGAME_H
#define SNAKEGAME_H

#include <vector>
#include "SnakePart.h"

class SnakeGame {
    std::vector<SnakePart> snake;
    int maxWidth, maxHeight;
    char direction;
    bool gameOver;
    int appleX, appleY;
    int score;
    int level;
    std::vector<std::pair<int, int>> obstacles;

public:
    SnakeGame(int level);
    ~SnakeGame();
    void draw();
    void input();
    void logic();
    bool isGameOver() const;
private:
    void generateApple();
    void generateObstacles();
    bool isObstacle(int x, int y);
    void drawObstacles();
    void growSnake();
    void moveSnake();
    bool checkCollision();
    bool isSnake(int x, int y);
};

#endif


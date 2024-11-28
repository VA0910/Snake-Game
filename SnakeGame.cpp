//author: 'Vaishnavi Agarwal'

#include <ncurses.h>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "SnakeGame.h"

using namespace std;

SnakeGame::SnakeGame(int level) : level(level) {
    initscr();
    start_color();              
    noecho();
    curs_set(0);
    timeout(100);                
    keypad(stdscr, TRUE);        
    getmaxyx(stdscr, maxHeight, maxWidth);
    srand(time(0));

    init_pair(1, COLOR_GREEN, COLOR_BLACK);  
    init_pair(2, COLOR_RED, COLOR_BLACK);    
    init_pair(3, COLOR_YELLOW, COLOR_BLACK); 

    snake.push_back(SnakePart(maxWidth / 2, maxHeight / 2));
    direction = 'r';
    gameOver = false;
    score = 0;

    generateApple();

    if (level == 2) {
        generateObstacles();
    }
}

SnakeGame::~SnakeGame() {
    endwin();
}
void SnakeGame::generateApple() {
    do {
        appleX = rand() % maxWidth;
        appleY = rand() % maxHeight;
    } while (isSnake(appleX, appleY) || (level == 2 && isObstacle(appleX, appleY)));
}

bool SnakeGame::isSnake(int x, int y) {
    for (const auto& part : snake) {
        if (part.x == x && part.y == y) {
            return true;
        }
    }
    return false;
}


void SnakeGame::generateObstacles() {
    int numObstacles = (maxWidth * maxHeight) / 100;  
    for (int i = 0; i < numObstacles; i++) {
        int ox = rand() % maxWidth;
        int oy = rand() % maxHeight;
        obstacles.push_back({ox, oy});
    }
}

bool SnakeGame::isObstacle(int x, int y) {
    for (const auto& obs : obstacles) {
        if (obs.first == x && obs.second == y)
            return true;
    }
    return false;
}
//creating the obstacles
void SnakeGame::drawObstacles() {
    attron(COLOR_PAIR(3));
    for (const auto& obs : obstacles) {
        mvprintw(obs.second, obs.first, "X");
    }
    attroff(COLOR_PAIR(3));
}

void SnakeGame::draw() {
    clear();
    mvprintw(0, 0, "Score: %d", score);

    attron(COLOR_PAIR(2)); 
    mvprintw(appleY, appleX, "A");
    attroff(COLOR_PAIR(2));

    //snake
    attron(COLOR_PAIR(1));
    for (auto& part : snake) {
        mvprintw(part.y, part.x, "#");
    }
    attroff(COLOR_PAIR(1));

    //level 2
    if (level == 2) {
        drawObstacles();
    }

    refresh();
}

void SnakeGame::input() {
    int ch = getch();
    switch (ch) {
        case KEY_UP:
            if(direction!='d') direction = 'u';
            break;
        case KEY_DOWN:
            if(direction!='u') direction = 'd';
            break;
        case KEY_LEFT:
            if(direction!='r') direction = 'l';
            break;
        case KEY_RIGHT:
            if(direction!='l') direction = 'r';
            break;
        case 'q':
            gameOver = true;
            break;
    }
}

void SnakeGame::moveSnake() {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'u': dy = -1; break;
        case 'd': dy = 1; break;
        case 'l': dx = -1; break;
        case 'r': dx = 1; break;
    }

    for (int i = snake.size() - 1; i > 0; i--) {
        snake[i] = snake[i - 1];
    }
    snake[0].x += dx;
    snake[0].y += dy;
}
void SnakeGame::logic() {
    if (snake[0].x == appleX && snake[0].y == appleY) {
        score++;
        generateApple(); 
        growSnake(); 
        cout << "Apple eaten! Score: " << score << endl;
    } else {
        moveSnake(); 
    }

    if (checkCollision()) {
        cout << "Collision detected! Game Over." << endl;
        gameOver = true;
    }
}

void SnakeGame::growSnake() {
    int dx = 0, dy = 0;
    switch (direction) {
        case 'u': dy = -1; break;
        case 'd': dy = 1; break;
        case 'l': dx = -1; break;
        case 'r': dx = 1; break;
    }
    
    SnakePart newPart = snake[0]; 
    newPart.x += dx;
    newPart.y += dy;

    for (const auto& part : snake) {
        if (newPart.x == part.x && newPart.y == part.y) {
            cout << "Self-collision detected while growing!" << endl; 
            gameOver = true; 
            return;
        }
    }

    snake.push_back(newPart); 
}

bool SnakeGame::checkCollision() {
    if (snake[0].x < 0 || snake[0].x >= maxWidth || snake[0].y < 0 || snake[0].y >= maxHeight) {
        return true;
    }
   
    for (size_t i = 1; i < snake.size(); i++) {
        if (snake[i].x == snake[0].x && snake[i].y == snake[0].y) {
            return true;
        }
    }

    if (level == 2 && isObstacle(snake[0].x, snake[0].y)) {
        return true;
    }

    return false;
}

bool SnakeGame::isGameOver() const {
    return gameOver;
}


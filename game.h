#ifndef GAME_H
#define GAME_H

#include "snake.h"

#define MAP_W 32
#define MAP_H 16

class Game
{
protected:
    Snake snake;
    QPaintDevice * qp;
    int score;

public:
    Game(QPaintDevice * qp);
    void draw();
    void next();
    void setPiece();
    int getScore();
};

#endif // GAME_H

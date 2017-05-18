#ifndef GAME_H
#define GAME_H

#include <vector>
#include <list>

#include "point.h"
#include "snake.h"


class Game
{
private:
    std::vector<std::vector<Point>> map;
    int w,h;
    Point * snack = nullptr;
    std::list<Point*> swallowed;
    Snake * snake = nullptr;
    int score = 0;
    void placeBorders();
    void placeSnack();
public:
    Game(bool borders);
    ~Game();
    int nextFrame();
    Point* getSnack();
    std::list<Point *> getSwallowed();
    int getScore();
    Snake * getSnake();
};

#endif // GAME_H

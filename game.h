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

    void placeSnack();
public:
    Game();
    ~Game();
    void nextFrame();
    Point* getSnack();
    std::list<Point *> getSwallowed();
    int getScore();
    Snake * getSnake();
};

#endif // GAME_H

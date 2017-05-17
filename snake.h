#ifndef SNAKE_H
#define SNAKE_H

#include <list>
#include <vector>

#include <QPainter>

#include "point.h"

#define MAP_W 32
#define MAP_H 32

#define START_LENGTH 4

#define DIRECTION_EAST  0
#define DIRECTION_SOUTH 1
#define DIRECTION_WEST  2
#define DIRECTION_NORTH 3

class Snake
{
    std::list<Point*> body; //List of points creating snake body
    int direction;         //Direction of snake
    std::vector<std::vector<Point>> &v; //Board
public:
    Snake(std::vector<std::vector<Point>> &v, int w, int startx, int starty);
    int nextFrame();         //Move snake. If snake encounters barrier returns 1
    void changeDirection(int d); //Change direction of snake
};

#endif // SNAKE_H

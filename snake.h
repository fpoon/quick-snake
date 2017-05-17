#ifndef SNAKE_H
#define SNAKE_H

#include <list>

#include <QPainter>

#include "point.h"

#define INITIAL_PIECES 4

#define DIRECTION_EAST  0
#define DIRECTION_SOUTH 1
#define DIRECTION_WEST  2
#define DIRECTION_NORTH 3

class Snake
{
    std::list<Point> body; //List of points creating snake body
    int direction;         //Direction of snake
public:
    Snake();
    int nextFrame();         //Move snake. If snake encounters barrier returns 1
    void draw(QPainter &qp); //Draw snake
    int snack(Point &snack); //Check if encouters snack
    void changeDirection(int d); //Change direction of snake
};

#endif // SNAKE_H

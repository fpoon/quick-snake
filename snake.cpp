#include <vector>

#include "snake.h"

using namespace std;

Snake::Snake(vector<vector<Point> > &v) : v(v)
{
    int startx = MAP_W/2;
    int starty = MAP_H/2;
    direction = DIRECTION_EAST;
    for (int i = 0; i < START_LENGTH; i++)
        body.push_back(&v[startx-i][starty]);
}

int Snake::nextFrame()
{
    int x,y;
    Point *head = body.front();
    Point *tail = body.back();

    switch (direction) {
    case DIRECTION_EAST:
        x = 1, y = 0;
        break;
    case DIRECTION_SOUTH:
        x = 0, y = 1;
        break;
    case DIRECTION_WEST:
        x = -1, y = 0;
        break;
    case DIRECTION_NORTH:
        x = 0, y = -1;
        break;
    default:
        break;
    }

    x += head->x;
    y += head->y;
    if (x >= MAP_W)
        x = 0;
    if (x < 0)
        x = MAP_W-1;
    if (y >= MAP_H)
        y = 0;
    if (y < 0)
        y = MAP_H-1;

    if (v[x][y].type == PTYPE_BORDER)
        return -1;
    if (v[x][y].type == PTYPE_SNACK)
    {
        body.push_back(tail);
    }

    head = &v[x][y];
    head->type = PTYPE_SNAKE;
    body.push_front(head);

    tail->type = PTYPE_NOTHING;
    body.pop_back();

    return 0;
}

void Snake::changeDirection(int d)
{
    if ((direction == DIRECTION_NORTH && d == DIRECTION_SOUTH) ||
        (direction == DIRECTION_SOUTH && d == DIRECTION_NORTH) ||
        (direction == DIRECTION_EAST && d == DIRECTION_WEST) ||
        (direction == DIRECTION_WEST && d == DIRECTION_EAST))
        return;

    direction = d;
}

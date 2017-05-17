#ifndef POINT_H
#define POINT_H

#define PTYPE_NOTHING 0
#define PTYPE_SNAKE 1
#define PTYPE_SNACK 2
#define PTYPE_BORDER 3

typedef struct Point {
    int x;
    int y;
    int type;
} Point;

#endif // POINT_H

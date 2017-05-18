#include "gamedrawer.h"

#include <list>
#include <cmath>

#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QKeyEvent>

#include "snake.h"

#define LESSER(x,y) x<y?x:y

using namespace std;

GameDrawer::GameDrawer(QWidget *parent) : QWidget(parent), snake(nullptr)
{
    map.resize(MAP_W);
    for (int x = 0; x < map.size(); x++)
        for (int y = 0; y < MAP_H; y++)
            map[x].push_back({x, y, PTYPE_NOTHING});
    startGame();
}

GameDrawer::~GameDrawer()
{
    if (snake)
        delete snake;
}

void GameDrawer::paintEvent(QPaintEvent *event)
{
    w = this->size().width();
    h = this->size().height();
    cellW = (float)w/(float)MAP_W;
    cellH = (float)h/(float)MAP_H;

    QPainter qp(this);
    qp.fillRect(0, 0, w, h, QColor(0,0,0));
    drawBorders(qp);
    drawSnake(qp);
}

void GameDrawer::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Space:
        snake->nextFrame();
        //printf("Space bar\n");
        break;
    case Qt::Key_Up:
        snake->changeDirection(DIRECTION_NORTH);
        break;
    case Qt::Key_Right:
        snake->changeDirection(DIRECTION_EAST);
        break;
    case Qt::Key_Down:
        snake->changeDirection(DIRECTION_SOUTH);
        break;
    case Qt::Key_Left:
        snake->changeDirection(DIRECTION_WEST);
        break;
    default:
        break;
    }
    this->repaint();
}

void GameDrawer::drawBorders(QPainter &qp)
{

    qp.setPen(QPen(QColor(128,255,0), LESSER(cellW,cellH)/2, Qt::SolidLine));
    qp.drawLine(cellW/2, cellH/2, w-cellW/2, cellH/2);
    qp.drawLine(cellW/2, cellH/2, cellW/2, h-cellH/2);
    qp.drawLine(w-cellW/2, cellH/2, w-cellW/2, h-cellH/2);
    qp.drawLine(cellW/2, h-cellH/2, w-cellW/2, h-cellH/2);
}

void GameDrawer::drawSnake(QPainter &qp)
{
    if (!snake)
        return;
    list<Point*> body(snake->body);
    //printf("Snake: %d\n", body.size());
    Point *head = body.front();
    body.pop_front();
    Point *next = body.front();

    qp.setPen(QPen(QColor(128,255,0), LESSER(cellW,cellH)/2, Qt::SolidLine));

    for (int i = 0; i < body.size()-1; i++) {
        if (abs(head->x - next->x) <= 1 && abs(head->y - next->y) <= 1)
            qp.drawLine(head->x*cellW+cellW/2, head->y*cellH+cellH/2,
                    next->x*cellW+cellW/2, next->y*cellH+cellH/2);
        head = next;
        body.pop_front();
        next = body.front();
    }
}

void GameDrawer::startGame()
{
    if (snake)
        delete snake;
    snake = new Snake(map);
    //snake->nextFrame();

}

#include "gamedrawer.h"

#include <list>
#include <cmath>
#include <cstdlib>
#include <string>

#include <QPainter>
#include <QColor>
#include <QBrush>
#include <QKeyEvent>
#include <QFont>
#include <QAction>
#include <QTimer>

#include "snake.h"

#define LESSER(x,y) ((x)<(y)?(x):(y))
#define GREATER(x,y) ((x)>(y)?(x):(y))

using namespace std;

GameDrawer::GameDrawer(QWidget *parent) : QWidget(parent)
{
    gameSpeed = SPEED_SLOW;
    gameState = GS_PAUSED;
    game = nullptr;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(nextFrame()));
    startGame(true, SPEED_SLOW);
}

GameDrawer::~GameDrawer()
{
    if (game)
        delete game;
    delete timer;
}

void GameDrawer::paintEvent(QPaintEvent *event)
{
    string s;
    w = this->size().width();
    h = this->size().height();

    QPainter qp(this);
    qp.fillRect(0, 0, w, h, QColor(0,0,0));
    h *= 0.9f;
    cellW = (float)w/(float)MAP_W;
    cellH = (float)h/(float)MAP_H;

    qp.setPen(QPen(QColor(128,255,0), LESSER(cellW,cellH)/2, Qt::SolidLine));
    qp.setFont(QFont("Monospace", size().height()*0.05));

    switch (gameState)
    {
        case GS_NO_GAME:
            qp.drawText(20, this->size().height()*0.55, "Snake? SNAKE?! SNAAAAKEE!!!");
        break;
        case GS_END:
            s = "Your score: ";
            s += to_string(game->getScore());
            qp.drawText(20, this->size().height()*0.55, s.c_str());
        break;
        case GS_PAUSED:
            qp.drawText(20, this->size().height()*0.55, "Click to play.");
        break;
        default:
            drawBorders(qp);
            drawSnacks(qp);
            drawSnake(qp);
            drawScore(qp);
        break;
    }
}

void GameDrawer::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Space)
        pause();

    if (gameState != GS_PLAY)
        return;
    Snake * snake = game->getSnake();

    switch (event->key()) {
    case Qt::Key_W:
    case Qt::Key_Up:
        snake->changeDirection(DIRECTION_NORTH);
        break;
    case Qt::Key_D:
    case Qt::Key_Right:
        snake->changeDirection(DIRECTION_EAST);
        break;
    case Qt::Key_S:
    case Qt::Key_Down:
        snake->changeDirection(DIRECTION_SOUTH);
        break;
    case Qt::Key_A:
    case Qt::Key_Left:
        snake->changeDirection(DIRECTION_WEST);
        break;
    default:
        break;
    }
    this->repaint();
}

void GameDrawer::mousePressEvent(QMouseEvent *event)
{
    pause();
}



void GameDrawer::drawBorders(QPainter &qp)
{
    if(!borders)
        return;
    qp.setPen(QPen(QColor(128,255,0), LESSER(cellW,cellH)/2, Qt::SolidLine));
    qp.drawLine(cellW/2, cellH/2, w-cellW/2, cellH/2);
    qp.drawLine(cellW/2, cellH/2, cellW/2, h-cellH/2);
    qp.drawLine(w-cellW/2, cellH/2, w-cellW/2, h-cellH/2);
    qp.drawLine(cellW/2, h-cellH/2, w-cellW/2, h-cellH/2);
}

void GameDrawer::drawSnake(QPainter &qp)
{
    Snake *snake = game->getSnake();
    if (!snake)
        return;
    list<Point*> body(snake->body);
    int size = body.size();
    //printf("Snake: %d\n", body.size());
    Point *head = body.front();
    body.pop_front();
    Point *next = body.front();

    qp.setPen(QPen(QColor(128,255,0), LESSER(cellW,cellH)/2, Qt::SolidLine));

    for (int i = 0; i < size-1; i++) {
        if (abs(head->x - next->x) <= 1 && abs(head->y - next->y) <= 1)
            qp.drawLine((float)head->x*cellW+cellW/2.f, (float)head->y*cellH+cellH/2.f,
                    (float)next->x*cellW+cellW/2.f, (float)next->y*cellH+cellH/2.f);
        head = next;
        body.pop_front();
        next = body.front();
        //printf ("i = %d\n", i);
    }
}

void GameDrawer::drawSnacks(QPainter &qp)
{
    Point *snack = game->getSnack();
    auto swallowed = game->getSwallowed();

    float xOff, yOff;
    if (cellW > cellH)
    {
        xOff = (GREATER(cellW, cellH)-LESSER(cellW, cellH))/2.f;
        yOff = 0;
    } else
    {
        yOff = (GREATER(cellW, cellH)-LESSER(cellW, cellH))/2.f;
        xOff = 0;
    }

    qp.setPen(QPen(QColor(128,255,0), 1, Qt::SolidLine));
    if (snack && snack->type == PTYPE_SNACK)
        qp.fillRect(snack->x*cellW+xOff, snack->y*cellH+yOff,
                    LESSER(cellW, cellH)+1, LESSER(cellW, cellH)+1,
                    QBrush(QColor(128,255,0), Qt::SolidPattern));
    for (auto p : swallowed)
        if (p && p->type == PTYPE_SNAKE)
            qp.fillRect(p->x*cellW+xOff, p->y*cellH+yOff,
                        LESSER(cellW, cellH)+1, LESSER(cellW, cellH)+1,
                        QBrush(QColor(128,255,0), Qt::SolidPattern));
}

void GameDrawer::drawDebugGrid(QPainter &qp)
{
    qp.setPen(QPen(QColor(128,128,128), 1, Qt::SolidLine));
    for (float x = 0; x < w; x += cellW)
         qp.drawLine(x, 0, x, h);
    for (float y = 0; y < h; y += cellH)
        qp.drawLine(0, y, w, y);
}

void GameDrawer::drawScore(QPainter &qp)
{
    string s = "Score: ";
    s += to_string(game->getScore());
    qp.setFont(QFont("Monospace", size().height()*0.05));
    qp.drawText(10, this->size().height()*0.975, s.c_str());
}

void GameDrawer::pause()
{
    switch (gameState) {
    case GS_PAUSED:
        gameState = GS_PLAY;
        break;
    case GS_PLAY:
        gameState = GS_PAUSED;
        break;
    case GS_END:
        startGame(borders, gameSpeed);
    default:
        break;
    }
    repaint();
}

void GameDrawer::startGame(bool borders, int speed)
{
    this->borders = borders;
    this->gameSpeed = speed;

    gameState = GS_PAUSED;
    if (game)
        delete game;
    if (timer->isActive())
        timer->stop();
    game = new Game(borders);
    timer->start(gameSpeed);
    repaint();

}

void GameDrawer::nextFrame()
{
    if (!game)
        return;
    Snake * snake = game->getSnake();
    if (gameState == GS_PLAY)
        if (game->nextFrame())
        {
            timer->stop();
            timer->start(SPEED_FAST);
            gameState = GS_LOST;
        }
    if (gameState == GS_LOST)
        if (snake->body.size() > 1)
            snake->body.pop_back();
        else
        {
            gameState = GS_END;
            timer->stop();
        }
    repaint();
}

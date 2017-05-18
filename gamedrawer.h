#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

#include <QWidget>
#include <QTimer>

#include "snake.h"
#include "game.h"

#define GS_NO_GAME 0
#define GS_END     1
#define GS_PAUSED  2
#define GS_PLAY    3

#define SPEED_SLOW 300
#define SPEED_MEDIUM 200
#define SPEED_FAST 100

class GameDrawer : public QWidget
{
    Q_OBJECT
public:
    explicit GameDrawer(QWidget *parent = 0);
    ~GameDrawer();
    void startGame(bool borders, int speed);
signals:

public slots:
    void nextFrame();
protected:
    std::vector<std::vector<Point>> map;
    int w,h;
    float cellW,cellH;
    int gameState;
    int gameSpeed;
    bool borders;
    QTimer * timer;

    Game * game;

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;
    void mousePressEvent(QMouseEvent* event) override;

    void drawBorders(QPainter &qp);
    void drawSnake(QPainter &qp);
    void drawSnacks(QPainter &qp);
    void drawDebugGrid(QPainter &qp);
    void drawScore(QPainter &qp);

};

#endif // GAMEDRAWER_H

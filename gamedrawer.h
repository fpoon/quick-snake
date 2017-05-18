#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

#include <QWidget>

#include "snake.h"
#include "game.h"

class GameDrawer : public QWidget
{
    Q_OBJECT
public:
    explicit GameDrawer(QWidget *parent = 0);
    ~GameDrawer();
signals:

public slots:
protected:
    std::vector<std::vector<Point>> map;
    int w,h;
    float cellW,cellH;
    int topOffset = 20;

    Game * game;

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawBorders(QPainter &qp);
    void drawSnake(QPainter &qp);
    void drawSnacks(QPainter &qp);
    void drawDebugGrid(QPainter &qp);
    void drawScore(QPainter &qp);
    void startGame();
};

#endif // GAMEDRAWER_H

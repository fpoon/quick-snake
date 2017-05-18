#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

#include <QWidget>

#include "snake.h"

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
    Point * snack = nullptr;
    std::list<Point*> swallowed;
    Snake * snake = nullptr;

    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent* event) override;

    void drawBorders(QPainter &qp);
    void drawSnake(QPainter &qp);
    void drawSnacks(QPainter &qp);
    void drawDebugGrid(QPainter &qp);
    void placeSnack();
    void startGame();
};

#endif // GAMEDRAWER_H

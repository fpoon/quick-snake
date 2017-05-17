#ifndef GAMEDRAWER_H
#define GAMEDRAWER_H

#include <QWidget>

#include "snake.h"

class GameDrawer : public QWidget
{
    Q_OBJECT
public:
    explicit GameDrawer(QWidget *parent = 0);

signals:

public slots:
protected:
    int w,h;
    int cellW,cellH;
    int topOffset = 20;
    void paintEvent(QPaintEvent *event) override;
    void drawBorders(QPainter &qp);
};

#endif // GAMEDRAWER_H

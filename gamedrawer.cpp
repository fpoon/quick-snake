#include "gamedrawer.h"

#include <QPainter>
#include <QColor>
#include <QBrush>

#define LESSER(x,y) x<y?x:y

GameDrawer::GameDrawer(QWidget *parent) : QWidget(parent)
{

}

void GameDrawer::paintEvent(QPaintEvent *event)
{
    w = this->size().width();
    h = this->size().height();
    cellW = w/MAP_W;
    cellH = h/MAP_H;

    QPainter qp(this);
    qp.fillRect(0, 0, w, h, QColor(0,0,0));
    drawBorders(qp);
}

void GameDrawer::drawBorders(QPainter &qp)
{

    qp.setPen(QPen(QColor(128,255,0), LESSER(cellW,cellH)/2, Qt::SolidLine));
    qp.drawLine(cellW/2, cellH/2, w-cellW/2, cellH/2);
    qp.drawLine(cellW/2, cellH/2, cellW/2, h-cellH/2);
    qp.drawLine(w-cellW/2, cellH/2, w-cellW/2, h-cellH/2);
    qp.drawLine(cellW/2, h-cellH/2, w-cellW/2, h-cellH/2);
}

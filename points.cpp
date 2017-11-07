#include "points.h"

Points::Points(int xPos, int yPos, int countPoint,  QObject *parent) : QObject(parent)
{
    count=0;
    setPen(Qt::NoPen);
    setRect(0, 0, 32, 16);
    setPos(xPos,yPos+16);
    switch (countPoint) {
    case 100:
        setBrush(QPixmap(":/img/100point.png"));
        break;
    case 200:
        setBrush(QPixmap(":/img/200point.png"));
        break;
    case 300:
        setBrush(QPixmap(":/img/300point.png"));
        break;
    case 400:
        setBrush(QPixmap(":/img/400point.png"));
        break;
    default:
        break;
    }
    emit addPoints(countPoint);
    this->setZValue(3);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(100);
}

void Points::move()
{
    setPos(x(),y()-2);
    count++;
    if(count==10){
        delete this;
    }
}

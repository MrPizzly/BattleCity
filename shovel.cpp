#include "shovel.h"

Shovel::Shovel(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    setPen(Qt::NoPen);
    setRect(0, 0, 32, 32);
    setPos(xPos,yPos);
    setBrush(QPixmap(":/img/shovel.png"));
    this->setZValue(2);
}

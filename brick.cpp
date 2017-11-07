#include "brick.h"

Brick::~Brick()
{
   emit delMapCoord(xPos,yPos,false);
}

Brick::Brick(int xPos, int yPos, QObject *parent): QObject(parent)
{
    this->xPos=xPos;
    this->yPos=yPos;
    setRect(xPos * 16, yPos * 16, 16, 16);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/brick.png"));
}

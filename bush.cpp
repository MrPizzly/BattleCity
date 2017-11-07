#include "bush.h"

Bush::Bush(int xPos, int yPos, QObject *parent): QObject(parent)
{
    this->xPos=xPos;
    this->yPos=yPos;
    setRect(xPos * 16, yPos * 16, 16, 16);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/bush.png"));
    this->setZValue(2);
}

Bush::~Bush()
{
    emit delMapCoord(xPos,yPos,false);
}

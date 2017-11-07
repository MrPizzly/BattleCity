#include "concrete.h"

Concrete::Concrete(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    this->xPos=xPos;
    this->yPos=yPos;
    setRect(xPos * 16, yPos * 16, 16, 16);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/concrete.png"));
}

Concrete::~Concrete()
{
    emit delMapCoord(xPos,yPos,false);
}

#include "base.h"

Base::Base(int xPos, int yPos, QObject *parent): QObject(parent)
{
    this->xPos=xPos;
    this->yPos=yPos;
    setRect(xPos * 16, yPos * 16, 32, 32);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/base.png"));
}

Base::~Base()
{
    emit delMapCoord(xPos,yPos,true);
}

void Base::gameLoss()
{
    setBrush(QPixmap(":/img/loss.png"));
}


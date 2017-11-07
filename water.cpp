#include "water.h"

Water::Water(int xPos, int yPos, QObject *parent): QObject(parent)
{
    setRect(xPos * 16, yPos * 16, 16, 16);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/water1.png"));
    this->setZValue(0);
}

Water::~Water()
{
    emit delMapCoord(xPos,yPos,false);
}

void Water::animate()
{
    if(animateFlag == 0){
        setBrush(QPixmap(":/img/water2.png"));
        animateFlag = 1;
    }
    else{
        setBrush(QPixmap(":/img/water1.png"));
        animateFlag = 0;
    }
}


#include "pause.h"

Pause::Pause(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    setPen(Qt::NoPen);
    setRect(0, 0, 80, 16);
    setPos(xPos,yPos);
    setBrush(QPixmap(":/img/pause.png"));
    this->setZValue(2);
}

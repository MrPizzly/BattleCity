#include "gameover.h"

GameOver::GameOver(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    setPen(Qt::NoPen);
    setRect(0, 0, 64, 32);
    setPos(xPos,yPos);
    setBrush(QPixmap(":/img/gameover.png"));
    this->setZValue(3);
    timer = new QTimer(this);
    connect(timer,SIGNAL(timeout()),this,SLOT(move()));
    timer->start(20);
    count=0;
}

void GameOver::move()
{
    setPos(x(),y()-2);
    count++;
    if(count>120){
        timer->stop();
    }
}

#include "shield.h"

Shield::Shield(int xPos, int yPos, QObject *parent): QObject(parent)
{
    setRect(0, 0, 32, 32);
    setPos(xPos,yPos);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/shield1.png"));
    animationTimer = new QTimer(this);
    connect(animationTimer,SIGNAL(timeout()),this,SLOT(animation()));
    animationTimer->start(100);
    this->setZValue(2);
    animate=true;
    deleted = new QTimer(this);
    connect(deleted,SIGNAL(timeout()),this,SLOT(del()));
    deleted->start(3000);

}

void Shield::start()
{
    deleted->start(deletedCount);
}

void Shield::pause()
{
    deletedCount=deleted->remainingTime();
    deleted->stop();
}

void Shield::animation()
{
    if(animate){
        setBrush(QPixmap(":/img/shield2.png"));
        animate=false;
    }
    else{
        setBrush(QPixmap(":/img/shield1.png"));
        animate=true;
    }
}

void Shield::move(char side)
{
    switch (side) {
    case 'D':
        setPos(x(),y()+2);
        break;
    case 'L':
        setPos(x()-2, y());
        break;
    case 'U':
        setPos(x(),y()-2);
        break;
    case 'R':
        setPos(x()+2,y());
        break;
    default:
        break;
    }
}

void Shield::del()
{
    delete this;
}

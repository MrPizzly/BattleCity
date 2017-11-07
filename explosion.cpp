#include "explosion.h"

Explosion::Explosion(int xPos, int yPos, bool tank, QObject *parent): QObject(parent)
{
    this->tank=tank;
    this->xPos=xPos;
    this->yPos=yPos;
    explosionPower=1;
    timer = new QTimer(this);
    setRect(0, 0, 32, 32);
    setPos(xPos,yPos);
    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/explosion1"));
    connect(timer,SIGNAL(timeout()),this,SLOT(power()));
    timer->start(100);
}


void Explosion::power()
{
    switch (explosionPower) {
    case 1:
        explosionPower++;
        setBrush(QPixmap(":/img/explosion2"));
        break;
    case 2:
        explosionPower++;
        setBrush(QPixmap(":/img/explosion3"));
        break;
    case 3:
        if(tank){
            explosionPower++;
            setRect(0, 0, 64, 64);
            setPos(x()-16,y()-16);
            setBrush(QPixmap(":/img/explosion4"));
        }
        else{
            delete this;
        }
        break;
    case 4:
        explosionPower++;
        setBrush(QPixmap(":/img/explosion5"));
        break;
    case 5:
        delete this;
        break;
    default:
        break;
    }
}

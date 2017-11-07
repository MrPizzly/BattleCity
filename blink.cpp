#include "blink.h"

Blink::Blink(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    this->xPos=xPos;
    this->yPos=yPos;
    count=0;
    setPen(Qt::NoPen);
    setRect(0, 0, 32, 32);
    setPos(xPos*16,yPos*16);
    setBrush(QPixmap(":/img/blink1.png"));
    this->setZValue(2);
    animate = new QTimer(this);
    connect(animate,SIGNAL(timeout()),this,SLOT(animation()));
    animate->start(75);
}

void Blink::start()
{
    animate->start(75);
}

void Blink::pause()
{
    animate->stop();
}

void Blink::animation()
{
    if(count==0){
        setBrush(QPixmap(":/img/blink2.png"));
        count++;
    }
    else if(count==1){
        setBrush(QPixmap(":/img/blink3.png"));
        count++;
    }
    else if(count==10){
        animate->stop();
        emit spawnEnemy(xPos,yPos);
        delete this;
    }
    else if(count%2==0){
        setBrush(QPixmap(":/img/blink4.png"));
        count++;
    }
    else{
        setBrush(QPixmap(":/img/blink3.png"));
        count++;
    }
}



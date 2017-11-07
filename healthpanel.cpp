#include "healthpanel.h"

HealthPanel::HealthPanel(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    setRect(0, 0, 16, 16);
    setPos(xPos,yPos);

    setPen(Qt::NoPen);
    setBrush(QPixmap(":/img/3.png"));
    this->setZValue(2);
}

void HealthPanel::changeHealth(int count)
{
    switch (count) {
    case 0:
        setBrush(QPixmap(":/img/0.png"));
        break;
    case 1:
        setBrush(QPixmap(":/img/1.png"));
        break;
    case 2:
        setBrush(QPixmap(":/img/2.png"));
        break;
    case 3:
        setBrush(QPixmap(":/img/3.png"));
        break;
    case 4:
        setBrush(QPixmap(":/img/4.png"));
        break;
    case 5:
        setBrush(QPixmap(":/img/5.png"));
        break;
    case 6:
        setBrush(QPixmap(":/img/6.png"));
        break;
    case 7:
        setBrush(QPixmap(":/img/7.png"));
        break;
    case 8:
        setBrush(QPixmap(":/img/8.png"));
        break;
    case 9:
        setBrush(QPixmap(":/img/9.png"));
        break;
    default:
        break;
    }
}

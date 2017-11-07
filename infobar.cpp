#include "infobar.h"

InfoBar::InfoBar(QObject *parent): QObject(parent)
{
    QGraphicsRectItem *health = new QGraphicsRectItem(432,256,8,8,this);
}

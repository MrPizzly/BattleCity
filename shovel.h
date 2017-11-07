#ifndef SHOVEL_H
#define SHOVEL_H

#include <QGraphicsRectItem>
#include <QPainter>


class Shovel: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Shovel(int xPos, int yPos, QObject *parent = 0);

};
#endif // SHOVEL_H

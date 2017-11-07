#ifndef GRANADE_H
#define GRANADE_H

#include <QGraphicsRectItem>
#include <QPainter>

class Granade: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Granade(int xPos, int yPos, QObject *parent = 0);

};

#endif // GRANADE_H

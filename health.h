#ifndef HEALTH_H
#define HEALTH_H

#include <QGraphicsRectItem>
#include <QPainter>

class Health: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Health(int xPos, int yPos, QObject *parent = 0);

};

#endif // HEALTH_H

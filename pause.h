#ifndef PAUSE_H
#define PAUSE_H

#include <QGraphicsRectItem>
#include <QPainter>

class Pause: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Pause(int xPos, int yPos, QObject *parent = 0);

};

#endif // PAUSE_H

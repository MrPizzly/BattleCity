#ifndef HELMET_H
#define HELMET_H

#include <QGraphicsRectItem>
#include <QPainter>

class Helmet: public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Helmet(int xPos, int yPos, QObject *parent = 0);

};

#endif // HELMET_H

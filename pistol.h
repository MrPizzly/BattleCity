#ifndef PISTOL_H
#define PISTOL_H

#include <QGraphicsRectItem>
#include <QPainter>

class Pistol: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Pistol(int xPos, int yPos, QObject *parent = 0);

};

#endif // PISTOL_H

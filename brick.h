#ifndef BRICK_H
#define BRICK_H

#include <QGraphicsRectItem>
#include <QPainter>

class Brick : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int xPos, yPos;
signals:
    void delMapCoord(int,int,bool);
public:
    explicit Brick(int xPos, int yPos, QObject *parent = 0);
    ~Brick();
};

#endif // BRICK_H

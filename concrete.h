#ifndef CONCRETE_H
#define CONCRETE_H

#include <QGraphicsRectItem>
#include <QPainter>

class Concrete : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int xPos, yPos;
signals:
    void delMapCoord(int,int,bool);
public:
    explicit Concrete(int xPos, int yPos, QObject *parent = 0);
    ~Concrete();
};

#endif // CONCRETE_H

#ifndef WATER_H
#define WATER_H

#include <QGraphicsRectItem>
#include <QPainter>

class Water : public QObject, public QGraphicsRectItem
{
    Q_OBJECT

public:
    explicit Water(int xPos, int yPos, QObject *parent = 0);
    ~Water();
signals:
    void delMapCoord(int,int,bool);
public slots:
    void animate();

private:
    bool animateFlag = 0;
    int xPos, yPos;
};

#endif // WATER_H

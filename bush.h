#ifndef BUSH_H
#define BUSH_H


#include <QGraphicsRectItem>
#include <QPainter>

class Bush : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int xPos, yPos;
signals:
    void delMapCoord(int,int,bool);
public:
    explicit Bush(int xPos, int yPos, QObject *parent = 0);
    ~Bush();
};

#endif // BUSH_H

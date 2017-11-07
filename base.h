#ifndef BASE_H
#define BASE_H


#include <QGraphicsRectItem>
#include <QPainter>

class Base : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int xPos, yPos;
signals:
    void delMapCoord(int,int,bool);
public:
    explicit Base(int xPos, int yPos, QObject *parent = 0);
    ~Base();
public slots:
    void gameLoss();
};

#endif // BASE_H

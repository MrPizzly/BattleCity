#ifndef POINTS_H
#define POINTS_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QTimer>

class Points: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Points(int xPos, int yPos, int count, QObject *parent = 0);
private:
    int count;
    QTimer *timer;
signals:
    void addPoints(int);
private slots:
    void move();
};

#endif // POINTS_H

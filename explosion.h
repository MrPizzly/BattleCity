#ifndef EXPLOSION_H
#define EXPLOSION_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QTimer>

class Explosion: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    bool tank;
    int xPos;
    int yPos;
    int explosionPower;
    QTimer *timer;
public:
    explicit Explosion(int xPos, int yPos, bool tank, QObject *parent = 0);
private slots:
    void power();
};

#endif // EXPLOSION_H

#ifndef BLINK_H
#define BLINK_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QTimer>

class Blink: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int xPos, yPos;
    int count;
    QTimer *animate;
public:
    explicit Blink(int xPos, int yPos, QObject *parent = 0);
signals:
    void spawnEnemy(int, int);
public slots:
    void start();
    void pause();
    void animation();
};

#endif // BLINK_H

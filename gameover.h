#ifndef GAMEOVER_H
#define GAMEOVER_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QTimer>

class GameOver: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    QTimer *timer;
    int count;
public:
    explicit GameOver(int xPos, int yPos, QObject *parent = 0);
public slots:
    void move();
};

#endif // GAMEOVER_H

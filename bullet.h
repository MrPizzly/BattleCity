#ifndef BULLET_H
#define BULLET_H

#include <QGraphicsRectItem>
#include <QObject>
#include <QTimer>
#include <QPainter>
#include <QList>
#include <typeinfo>

#include "concrete.h"
#include "brick.h"
#include "enemy.h"
#include "base.h"
#include "player.h"


class Bullet : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
    int id;
    int saveTimer;
    int stars;
    int count;
    int xPos;
    int yPos;
    char side;
    QTimer *timer;
    int BulletId;
    static int StaticId;
public:
    void startTimer();
    explicit Bullet(int xPos, int yPos, char side, int stars, int id,QObject *parent = 0);
    ~Bullet();
signals:
    void delBullet(int);
    void changeHealth(int);
    void enemyListing(QVector<Enemy*> *buff);
    void killBase();
    void CheckShield();
    void spawnExplosion(int,int,bool);
public slots:
    void start();
    void pause();
    void move();
};

#endif // BULLET_H

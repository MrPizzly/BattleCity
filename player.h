#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QList>
#include <QKeyEvent>
#include <QTimer>
#include <QList>
#include <typeinfo>

#include "stars.h"
#include "helmet.h"
#include "pistol.h"
#include "bush.h"
#include "shovel.h"
#include "granade.h"
#include "health.h"

class Player : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    Player(int xPos, int yPos, QObject *parent = 0);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void spawnShiledPlayer();
    int getX();
    int getY();
private:
    int saveTimer, saveDelShield;
    int posX, posY;
    int stars;
    int xPos, yPos;
    QList<int> *queue;
    int direction;
    char side;
    QTimer *timer;
    int count;
    int pressKey;
    bool animation;
    QTimer *delShield;
    bool shield;
    void changeView(int);
    int pistol;
signals:
    void checkPause();
    void addHealth();
    void CheckHealth();
    void killEnemy();
    void spawnShovel();
    void moveShield(char);
    void spawnShield(int,int);
    void changeCoord(int, int);
    void checkCoord(int, int, int, bool&);
    void spawnBullet(int, int, char, int, int);
private slots:
    void start();
    void pause();
    void CheckShield();
    void deleteShield();
    void move();


};

#endif // PLAYER_H

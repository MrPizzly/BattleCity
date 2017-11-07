#ifndef ENEMY_H
#define ENEMY_H

#include <QGraphicsRectItem>
#include <QPainter>
#include <QTimer>


class Enemy: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Enemy(int xPos, int yPos, int speedSh0ot, int speed, int health,QObject *parent = 0);
    ~Enemy();
    int getX();
    int getY();
    int getHealth();
    int getId();
    int getSpeed();
    int getSpeedShoot();
    void setHealth(int health);
    QTimer *timer;
private:
    int speedShoot;
    int saveTimer, saveTimerAnimation, saveTimerBullet;
    int speed;
    int health;
    bool animation;
    int xPos, yPos, posX, posY;
    static int StaticId;
    int EnemyId;
    char side;
    int count;

    QTimer *timerAnimation;
    QTimer *timerBullet;
signals:
    void spawnPoint(int, int, int);
    void spawnExplosion(int,int,bool);
    void delMapCoord(int,int,bool,char);
    void spawnBullet(int,int,char, int, int);
    void checkCoord(int,int,char, int);
    void changeCoord(int,int,char, int);
private slots:
    void changeHealth(int id);
    void start();
    void pause();
    void spawnBulletEnemy();
    void TankAnimation();
    void move();
    void motion(char side ,bool flag, int id);
};

#endif // ENEMY_H

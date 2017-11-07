#include "bullet.h"

void Bullet::startTimer()
{
    timer->stop();
    timer->start(10);
}

Bullet::Bullet(int xPos, int yPos, char side, int stars, int id ,QObject *parent): QObject(parent)
{
    this->id=id;
    this->stars=stars;
    count = 0;
    this->xPos=xPos;
    this->yPos=yPos;
    BulletId=StaticId;
    StaticId++;
    this->side=side;
    setPen(Qt::NoPen);
    setRect(0, 0, 8, 8);
    switch (side) {
    case 'D':
        setPos(xPos+12, yPos+32);
        this->setBrush(QPixmap(":/img/bulletDown.png"));
        break;
    case 'R':

        setPos(xPos+32,yPos+12);
        this->setBrush(QPixmap(":/img/bulletRight.png"));
        break;
    case 'U':
        setPos(xPos+12,yPos-8);
        setBrush(QPixmap(":/img/bulletUp.png"));
        break;
    case 'L':

        setPos(xPos-8,yPos+12);
        setBrush(QPixmap(":/img/bulletLeft.png"));
        break;
    default:
        break;
    }
    emit move();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(move()));
    if(stars==-2)
        timer->start(5);
    else
        timer->start(10);
}

Bullet::~Bullet()
{
    emit delBullet(id);
}

void Bullet::start()
{
    timer->start(10);
}

void Bullet::pause()
{
    saveTimer=timer->remainingTime();
    timer->stop();
}
int Bullet::StaticId = 1;

void Bullet::move()
{

    if((xPos<0) or (xPos>384) or (yPos<0) or (yPos>416)){
        switch (side) {
        case 'D':
            emit spawnExplosion(xPos,yPos-32,false);
            break;
        case 'L':
            emit spawnExplosion(xPos,yPos,false);
            break;
        case 'U':
            emit spawnExplosion(xPos,yPos,false);
            break;
        case 'R':
            emit spawnExplosion(xPos,yPos,false);
            break;
        default:
            break;
        }
        delete this;
    }
    bool deleted = false;
        QList<QGraphicsItem *> colliding_items = collidingItems();
        for(int i = 0; i < colliding_items.size(); i++){
            if(typeid(*(colliding_items[i])) == typeid(Brick)){
                switch (side) {
                case 'D':
                    emit spawnExplosion(xPos,yPos+24,false);
                    break;
                case 'L':
                    emit spawnExplosion(xPos-24,yPos,false);
                    break;
                case 'U':
                    emit spawnExplosion(xPos,yPos-24,false);
                    break;
                case 'R':
                    emit spawnExplosion(xPos+24,yPos,false);
                    break;
                default:
                    break;
                }
                delete colliding_items[i];
                deleted = true;

            }
            else if(typeid(*(colliding_items[i])) == typeid(Concrete))
            {
                switch (side) {
                case 'D':
                    emit spawnExplosion(xPos,yPos+24,false);
                    break;
                case 'L':
                    emit spawnExplosion(xPos-24,yPos,false);
                    break;
                case 'U':
                    emit spawnExplosion(xPos,yPos-24,false);
                    break;
                case 'R':
                    emit spawnExplosion(xPos+24,yPos,false);
                    break;
                default:
                    break;
                }
                if(stars>=3)
                    delete colliding_items[i];
                deleted = true;

            }
            else if(typeid(*(colliding_items[i])) == typeid(Bullet))
            {

                delete colliding_items[i];
                deleted = true;

            }
            else if(typeid(*(colliding_items[i])) == typeid(Enemy))
            {
                QVector<Enemy*> *buff = new QVector<Enemy *>;
                emit enemyListing(buff);
                for(int j=0;j<buff->size();j++){
                    if(colliding_items[i]->x()==buff->at(j)->getX() and colliding_items[i]->y()==buff->at(j)->getY()){
                        if(buff->at(j)->getHealth()<=1){
                            if(stars>=0){
                                delete colliding_items[i];
                                break;
                            }
                        }
                        else{
                            emit changeHealth(buff->at(j)->getId());
                            switch (side) {
                            case 'D':
                                emit spawnExplosion(xPos,yPos+24,false);
                                break;
                            case 'L':
                                emit spawnExplosion(xPos-24,yPos,false);
                                break;
                            case 'U':
                                emit spawnExplosion(xPos,yPos-24,false);
                                break;
                            case 'R':
                                emit spawnExplosion(xPos+24,yPos,false);
                                break;
                            default:
                                break;
                            }
                            break;
                        }
                    }
                }
                deleted = true;
                delete buff;
            }
            else if(typeid(*(colliding_items[i])) == typeid(Base))
            {
                emit killBase();
                deleted = true;
            }
            else if(typeid(*(colliding_items[i])) == typeid(Player))
            {
                emit CheckShield();
                deleted = true;
            }
        }
        if(deleted){
            delete this;
            return;
        }

    switch (side) {
    case 'D':
        yPos+=2;
        setPos(x(),y()+2);
        break;
    case 'L':
        xPos-=2;
        setPos(x()-2, y());
        break;
    case 'U':
        yPos-=2;
        setPos(x(),y()-2);
        break;
    case 'R':
        xPos+=2;
        setPos(x()+2,y());
        break;
    default:
        break;
    }

}

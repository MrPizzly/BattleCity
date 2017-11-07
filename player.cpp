#include "player.h"

Player::Player(int xPos, int yPos, QObject *parent) : QObject(parent)
{
    setFlag(QGraphicsItem::ItemIsFocusable);
    setFocus();
    setPen(Qt::NoPen);
    setRect(xPos * 16, yPos * 16, 32, 32);
    setBrush(QPixmap(":/img/player1up.png"));
    this->setZValue(1);
    queue = new QList<int>();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(move()));
    direction = 0;
    side = 'U';
    timer->start(20);
    count = 0;
    stars = 0;
    pistol = 0;
    pressKey = 0;
    posX=xPos*16;
    posY=yPos*16;
    this->xPos = xPos;
    this->yPos = yPos;
    shield = false;
    delShield = new QTimer(this);
    connect(delShield,SIGNAL(timeout()),this,SLOT(deleteShield()));
    spawnShiledPlayer();
    
}

void Player::keyPressEvent(QKeyEvent *event)
{
    if(event->key()==Qt::Key_Up
     ||event->key()==Qt::Key_Down
     ||event->key()==Qt::Key_Left
     ||event->key()==Qt::Key_Right){
        if(event->isAutoRepeat())
            event->ignore();
        else if(queue->size() < 2){
            if(queue->isEmpty()){
                queue->push_back(event->key());
            }
            else if(queue->first() != event->key()){
                queue->push_back(event->key());
            }
        }
    }
    else if(event->key()==Qt::Key_Space){
        emit spawnBullet(posX, posY, side,stars, -1);
    }
    else if(event->key()==Qt::Key_P){
        emit checkPause();
    }
}
void Player::keyReleaseEvent(QKeyEvent *event)
{
    if( !queue->isEmpty()){
    if(event->isAutoRepeat())
    {
        event->ignore();
    }
    else
    {
        switch(event->key()){
        case Qt::Key_Up:
            if(queue->first() == Qt::Key_Up){
                queue->pop_front();
            }
            else if(queue->last() == Qt::Key_Up){
                queue->pop_back();
            }
            break;
        case Qt::Key_Down:
            if(queue->first() == Qt::Key_Down){
                queue->pop_front();
            }
            else if(queue->last() == Qt::Key_Down){
                queue->pop_back();
            }
            break;
        case Qt::Key_Left:
            if(queue->first() == Qt::Key_Left){
                queue->pop_front();
            }
            else if(queue->last() == Qt::Key_Left){
                queue->pop_back();
            }
            break;
        case Qt::Key_Right:
            if(queue->first() == Qt::Key_Right){
                queue->pop_front();
            }
            else if(queue->last() == Qt::Key_Right){
                queue->pop_back();
            }
            break;
        }
    }
    }
}

void Player::spawnShiledPlayer()
{

    if(!shield){
        emit spawnShield(posX,posY);
        shield=true;
        delShield->start(3000);
    }

}

int Player::getX()
{
    return posX;
}

int Player::getY()
{
    return posY;
}

void Player::move()
{
    timer->start(20);
    QList<QGraphicsItem *> colliding_items = collidingItems();
    for(int i = 0; i < colliding_items.size(); i++){
        if(typeid(*(colliding_items[i])) == typeid(Stars)){
            delete colliding_items[i];
            stars++;
        }
        else if(typeid(*(colliding_items[i])) == typeid(Helmet)){
            delete colliding_items[i];
            spawnShiledPlayer();
        }
        else if(typeid(*(colliding_items[i])) == typeid(Pistol)){
            delete colliding_items[i];
            pistol++;
        }
        else if(typeid(*(colliding_items[i])) == typeid(Bush)){
            if(pistol>=2){
                delete colliding_items[i];
            }
        }
        else if(typeid(*(colliding_items[i])) == typeid(Shovel)){
            delete colliding_items[i];
            emit spawnShovel();
        }
        else if(typeid(*(colliding_items[i])) == typeid(Health)){
            delete colliding_items[i];
            emit addHealth();
        }
        else if(typeid(*(colliding_items[i])) == typeid(Granade)){
            delete colliding_items[i];
            emit killEnemy();
        }


    }


    if(direction == 0 and !queue->isEmpty()){
        direction = queue->last();
        this->changeView(direction);
        bool tmp;
        emit checkCoord(xPos, yPos, direction, tmp);
        if(!tmp){
            direction=0;
            return;
        }

    }
    switch(direction){
    case Qt::Key_Up:
        posY-=2;
        setPos(x(), y()-2);
        count++;
        emit moveShield('U');
        if(animation == 0){
            this->setBrush(QPixmap(":/img/player2up"));
            animation = 1;
        }
        else{
            this->setBrush(QPixmap(":/img/player1up"));
            animation = 0;
        }
        break;
    case Qt::Key_Down:
        posY+=2;
        setPos(x(), y()+2);
        count++;
        emit moveShield('D');
        if(animation == 0){
            this->setBrush(QPixmap(":/img/player2down"));
            animation = 1;
        }
        else{
            this->setBrush(QPixmap(":/img/player1down"));
            animation = 0;
        }
        break;
    case Qt::Key_Left:
        posX-=2;
        setPos(x()-2, y());
        count++;
        emit moveShield('L');
        if(animation == 0){
            this->setBrush(QPixmap(":/img/player2left"));
            animation = 1;
        }
        else{
            this->setBrush(QPixmap(":/img/player1left"));
            animation = 0;
        }
        break;
    case Qt::Key_Right:
        posX+=2;
        setPos(x()+2, y());
        count++;
        emit moveShield('R');
        if(animation == 0){
            this->setBrush(QPixmap(":/img/player2right"));
            animation = 1;
        }
        else{
            this->setBrush(QPixmap(":/img/player1right"));
            animation = 0;
        }
        break;
    }
    if(count >=8){
        switch(direction){
        case Qt::Key_Up:
            yPos--;
            emit changeCoord(xPos, yPos);
            break;
        case Qt::Key_Down:
            yPos++;
            emit changeCoord(xPos, yPos);
            break;
        case Qt::Key_Left:
            xPos--;
            emit changeCoord(xPos, yPos);
            break;
        case Qt::Key_Right:
            xPos++;
            emit changeCoord(xPos, yPos);
            break;
        }
       count = 0;
       direction = 0;
    }
}

void Player::changeView(int direction)
{
    if(direction == Qt::Key_Up and side != 'U')
        side = 'U';
    else if(direction == Qt::Key_Down and side != 'D')
        side = 'D';
    else if(direction == Qt::Key_Left and side != 'L')
        side = 'L';
    else if(direction == Qt::Key_Right and side != 'R')
        side = 'R';
    switch(direction){
    case Qt::Key_Up:
        this->setBrush(QPixmap(":/img/player1up.png"));
        animation = 0;
        break;
    case Qt::Key_Down:
        this->setBrush(QPixmap(":/img/player1down.png"));
        animation = 0;
        break;
    case Qt::Key_Left:
        this->setBrush(QPixmap(":/img/player1left.png"));
        animation = 0;
        break;
    case Qt::Key_Right:
        this->setBrush(QPixmap(":/img/player1right.png"));
        animation = 0;
        break;
    }
}

void Player::start()
{
    timer->start(saveTimer);
    delShield->start(saveDelShield);
}

void Player::pause()
{
    saveDelShield=delShield->remainingTime();
    saveTimer=timer->remainingTime();
    timer->stop();
    delShield->stop();
}

void Player::CheckShield()
{
    if(!shield){
        //spawnShiledPlayer();
        emit CheckHealth();
        clearFocus();
        delete this;
    }
}

void Player::deleteShield()
{
    shield=false;
    delShield->stop();
}

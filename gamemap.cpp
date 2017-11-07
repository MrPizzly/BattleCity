#include "gamemap.h"

#include <QTextStream>

GameMap::GameMap(QGraphicsScene *workScene, QObject *parent) : QObject(parent)
{
    points=0;
    pauseMessage = new Pause(168,208,this);
    paused=false;
    countEnemy=0;
    this->workScene = workScene;
    health=3;
    for(int i = 0; i < 26; i++)
        for(int j = 0; j < 26; j++)
            map[i][j] = 0;


    animationTimer = new QTimer(this);
    animationTimer->start(1000);
    showInterface();
    loadEnemys();
    loadMap();
    bullerId= new QVector<int>;
}

void GameMap::showInterface()
{
    HealthPanel *healthPanel = new HealthPanel(456,256,this);
    connect(this,SIGNAL(changeHealth(int)),healthPanel,SLOT(changeHealth(int)));
    workScene->addItem(healthPanel);


    QGraphicsRectItem *iconHealth = new QGraphicsRectItem(0,0,16,16,NULL);
    iconHealth->setPos(456-16,256);
    iconHealth->setBrush(QPixmap(":/img/health.png"));
    iconHealth->setPen(Qt::NoPen);
    workScene->addItem(iconHealth);

    QGraphicsRectItem *playerIcon = new QGraphicsRectItem(0,0,32,16,NULL);
    playerIcon->setPos(456-16,256-16);
    playerIcon->setBrush(QPixmap(":/img/playerIcon.png"));
    playerIcon->setPen(Qt::NoPen);
    workScene->addItem(playerIcon);

    for(int i=0;i<20;i++){
        QGraphicsRectItem *enemyIcon = new QGraphicsRectItem(0,0,16,16,NULL);
        if(i%2==0){
            enemyIcon->setPos(456-16,32+i/2*16);
            enemyIcon->setBrush(QPixmap(":/img/enemy.png"));
            enemyIcon->setPen(Qt::NoPen);
            workScene->addItem(enemyIcon);
        }
        else{
            enemyIcon->setPos(456,32+i/2*16);
            enemyIcon->setBrush(QPixmap(":/img/enemy.png"));
            enemyIcon->setPen(Qt::NoPen);
            workScene->addItem(enemyIcon);
        }
        enemyList.push_back(enemyIcon);
    }
}

void GameMap::createPlayer(int xPos, int yPos)
{
    map[xPos][yPos] = 1;
    map[xPos+1][yPos] = 1;
    map[xPos][yPos+1] = 1;
    map[xPos+1][yPos+1] = 1;
    Player *player = new Player(xPos, yPos, this);
    workScene->addItem(player);
    player->setFlag(QGraphicsItem::ItemIsFocusable);
    player->setFocus();
    connect(player, SIGNAL(spawnShield(int,int)),this,SLOT(spawnShield(int,int)));
    connect(player, SIGNAL(changeCoord(int,int)), this, SLOT(changePlayerCoord(int,int)));
    connect(player, SIGNAL(checkCoord(int,int,int,bool&)), this, SLOT(checkPlayerCoord(int,int,int,bool&)));
    connect(player, SIGNAL(spawnBullet(int,int,char, int, int)), this, SLOT(spawnBullet(int,int,char, int, int)));
    connect(player,SIGNAL(moveShield(char)),this,SLOT(moveShieldSlot(char)));
    connect(player,SIGNAL(spawnShovel()),this,SLOT(createShovel()));
    connect(player,SIGNAL(killEnemy()),this,SLOT(killEnemy()));
    connect(player,SIGNAL(CheckHealth()),this,SLOT(CheckHealth()));
    connect(player,SIGNAL(addHealth()),this,SLOT(addHealth()));
    connect(player,SIGNAL(checkPause()),this,SLOT(checkPause()));
    connect(this,SIGNAL(CheckShield()),player,SLOT(CheckShield()));
    connect(this,SIGNAL(pause()),player,SLOT(pause()));
    connect(this,SIGNAL(start()),player,SLOT(start()));
    emit spawnShield(player->getX(),player->getY());
}

void GameMap::createBase(int xPos, int yPos)
{
    map[xPos][yPos] = 7;
    map[xPos+1][yPos] = 7;
    map[xPos][yPos+1] = 7;
    map[xPos+1][yPos+1] = 7;
    Base *base= new Base(xPos, yPos, this);
    connect(this,SIGNAL(gameLoss()),base,SLOT(gameLoss()));
    workScene->addItem(base);
}

void GameMap::createBlock(int xPos, int yPos, int idBlock)
{
    switch(idBlock){
    case 2:
        {
        Brick *brick = new Brick(xPos, yPos, this);
        connect(brick,SIGNAL(delMapCoord(int,int,bool)),this,SLOT(delMapCoord(int,int,bool)));
        workScene->addItem(brick);
        break;
        }
    case 3:
        {
        Concrete *concrete = new Concrete(xPos, yPos, this);
        connect(concrete,SIGNAL(delMapCoord(int,int,bool)),this,SLOT(delMapCoord(int,int,bool)));
        workScene->addItem(concrete);
        break;
        }
    case 4:
        {
        Water *water = new Water(xPos, yPos, this);
        connect(water,SIGNAL(delMapCoord(int,int,bool)),this,SLOT(delMapCoord(int,int,bool)));
        workScene->addItem(water);

        connect(animationTimer, SIGNAL(timeout()), water, SLOT(animate()));
        break;
        }
    case 5:
        {

        Bush *bush = new Bush(xPos, yPos, this);
        connect(bush,SIGNAL(delMapCoord(int,int,bool)),this,SLOT(delMapCoord(int,int,bool)));
        workScene->addItem(bush);
        break;
        }
    case 6:
        {
        Ice *ice = new Ice(xPos, yPos, this);
        workScene->addItem(ice);
        break;
        }
    }
}

void GameMap::delBullet(int id)
{
    auto it=bullerId->begin();
    for(int i=0;i<bullerId->size();i++){
        if(bullerId->at(i)==id){
            bullerId->erase(it);
        }
        it++;
    }

}

void GameMap::spawnPoint(int xPos, int yPos, int count)
{
    Points *point = new Points(xPos,yPos,count,this);
    points+=count;
    workScene->addItem(point);
}

void GameMap::chengeHealthSlot(int id)
{
    chengeHealthSignal(id);
}

void GameMap::enemyListing(QVector<Enemy *> *buff)
{

    for(int i=0;i<enemyListObject.size();i++){
        buff->push_back(enemyListObject[i]);
    }

}

void GameMap::checkPause()
{
    if(paused){
        blinkTimer->start(saveBlinkTimer);
        stars->start(saveStars);
        emit start();
        paused=false;
        workScene->removeItem(pauseMessage);
    }
    else{
        saveStars=stars->remainingTime();
        saveBlinkTimer=blinkTimer->remainingTime();
        stars->stop();
        blinkTimer->stop();
        paused=true;
        emit pause();
        workScene->addItem(pauseMessage);
    }
}

void GameMap::killBase()
{
    end();
    emit gameLoss();}

void GameMap::spawnEnemy(int xPos, int yPos)
{
    Enemy *en;
    if(enemyQueue[countEnemy]==1)
        en = new Enemy(xPos,yPos,1,1,0,this);
    else if(enemyQueue[countEnemy]==2)
        en = new Enemy(xPos,yPos,1,2,0,this);
    else if(enemyQueue[countEnemy]==3)
        en = new Enemy(xPos,yPos,4,1,0,this);
    else if(enemyQueue[countEnemy]==4)
        en = new Enemy(xPos,yPos,1,1,4,this);
    enemyListObject.push_back(en);
    countEnemy++;
    connect(this,SIGNAL(motion(char,bool,int)),en,SLOT(motion(char,bool,int)));
    connect(en,SIGNAL(checkCoord(int,int,char,int)),this, SLOT(checkCoord(int,int,char,int)));
    connect(en,SIGNAL(changeCoord(int,int,char,int)),this, SLOT(changeCoord(int,int,char,int)));
    connect(en,SIGNAL(spawnBullet(int,int,char, int, int)),this, SLOT(spawnBullet(int,int,char, int, int)));
    connect(en,SIGNAL(spawnExplosion(int,int,bool)),this,SLOT(spawnExplosion(int,int,bool)));
    connect(en,SIGNAL(delMapCoord(int,int,bool,char)),this,SLOT(delMapCoord(int,int,bool,char)));
    connect(en,SIGNAL(spawnPoint(int,int,int)),this,SLOT(spawnPoint(int,int,int)));
    connect(this,SIGNAL(pause()),en,SLOT(pause()));
    connect(this,SIGNAL(start()),en,SLOT(start()));
    connect(this,SIGNAL(chengeHealthSignal(int)),en,SLOT(changeHealth(int)));
    workScene->addItem(en);
    removeEnemyInterfase();
}

void GameMap::removeEnemyInterfase()
{
    auto it=enemyList.last();
    delete it;
    enemyList.pop_back();
}

int GameMap::getPoints()
{
    return points;
}

void GameMap::addHealth()
{
    if(health<=9)
    health++;
    emit changeHealth(health);
}

void GameMap::killEnemy()
{
    QList<QGraphicsItem *> enemy_items = workScene->items();
    for(int i = 0; i < enemy_items.size(); i++){
        if(typeid(*(enemy_items[i])) == typeid(Enemy)){
            delete enemy_items[i];
            enemyListObject.pop_back();
        }

    }
}

void GameMap::deleteShovel()
{

    for(int i=shovel.size()-1;i>=shovel.size()-8;i--)
    {

        delete shovel[i];

    }
    //shovel.clear();
    timerShovel->stop();
}

void GameMap::createShovel()
{
    int i=shovel.size();
    shovel.push_back(new Concrete(11,23,this));
    shovel.push_back(new Concrete(12,23,this));
    shovel.push_back(new Concrete(13,23,this));
    shovel.push_back(new Concrete(14,23,this));
    shovel.push_back(new Concrete(11,24,this));
    shovel.push_back(new Concrete(11,25,this));
    shovel.push_back(new Concrete(14,24,this));
    shovel.push_back(new Concrete(14,25,this));
    for(i;i<shovel.size();i++)
    {
        workScene->addItem(shovel[i]);
    }
    timerShovel->start(5000);

}

void GameMap::moveShieldSlot(char side)
{
    emit moveShideld(side);
}

void GameMap::spawnShield(int xPos, int yPos)
{
    Shield *shield = new Shield(xPos,yPos,this);
    connect(this,SIGNAL(moveShideld(char)),shield,SLOT(move(char)));
    connect(this,SIGNAL(start()),shield,SLOT(start()));
    connect(this,SIGNAL(pause()),shield,SLOT(pause()));
    workScene->addItem(shield);
}

void GameMap::spawnBlink()
{
    blinkTimer->stop();
    blinkTimer->start(5000);
    int xPos, yPos = 0;
    xPos = qrand()%3;
    xPos*=12;
    Blink *blink = new Blink(xPos,yPos,this);
    connect(blink,SIGNAL(spawnEnemy(int,int)),this,SLOT(spawnEnemy(int,int)));
    connect(this,SIGNAL(pause()),blink,SLOT(pause()));
    connect(this,SIGNAL(start()),blink,SLOT(start()));
    workScene->addItem(blink);
    if(countEnemy>=19)
        blinkTimer->stop();

}

void GameMap::CheckShieldSlot()
{
    emit CheckShield();
}

void GameMap::CheckHealth()
{
    if(health>0){
       health--;
       emit changeHealth(health);
       this->createPlayer(8,24);
    }
    else{
        end();
    }
}

void GameMap::delMapCoord(int xPos, int yPos, bool tank, char side){
    switch (side) {
    case 'D':
        map[xPos][yPos+1]=0;
        map[xPos+1][yPos+1]=0;
        map[xPos][yPos+2]=0;
        map[xPos+1][yPos+2]=0;
        break;
    case 'L':
        map[xPos][yPos]=0;
        map[xPos][yPos+1]=0;
        map[xPos-1][yPos]=0;
        map[xPos-1][yPos+1]=0;
        break;
    case 'U':
        map[xPos][yPos]=0;
        map[xPos][yPos-1]=0;
        map[xPos+1][yPos]=0;
        map[xPos+1][yPos-1]=0;
        break;
    case 'R':
        map[xPos+1][yPos]=0;
        map[xPos+1][yPos+1]=0;
        map[xPos+2][yPos]=0;
        map[xPos+2][yPos+1]=0;
        break;
    default:
        break;
    }
    auto it=enemyListObject.begin();
    for(int i=0;i<enemyListObject.size();i++){
        if(enemyListObject[i]->getX()==xPos and enemyListObject[i]->getY()==yPos)
            enemyListObject.erase(it);
        it++;
    }
    //Base *a1 = new Base(xPos,yPos,0);
    //workScene->addItem(a1);
}

void GameMap::delMapCoord(int xPos, int yPos, bool tank)
{
    if(tank){
        map[xPos][yPos]=0;
        map[xPos+1][yPos]=0;
        map[xPos][yPos+1]=0;
        map[xPos+1][yPos+1]=0;
    }
    else{
        map[xPos][yPos]=0;
    }
    //Concrete *a = new Concrete(xPos,yPos,0);
    //workScene->addItem(a);

}

void GameMap::spawnExplosion(int xPos, int yPos, bool tank)
{
    Explosion *exp = new Explosion(xPos, yPos, tank);
    workScene->addItem(exp);
}

void GameMap::changePlayerCoord(int xPos, int yPos)
{
    for(int i = 0; i < 26; i++)
        for(int j = 0; j < 26; j++)
            if(map[i][j] == 1)
                map[i][j] = 0;
    map[xPos][yPos] = 1;
    map[xPos+1][yPos] = 1;
    map[xPos][yPos+1] = 1;
    map[xPos+1][yPos+1] = 1;
}

void GameMap::checkCoord(int xPos, int yPos, char side, int id)
{
    int n=rand()%4;
    char s;
    switch (n) {
    case 0:
        s='D';
        break;
    case 1:
        s='L';
        break;
    case 2:
        s='U';
        break;
    case 3:
        s='R';
        break;
    default:
        break;
    }

    switch (s) {
    case 'D':
        if(side!='U'){
            if(yPos==24){
                break;
            }
            else{
                if((map[xPos][yPos+2]==0 and map[xPos+1][yPos+2]==0)
                        ||(map[xPos][yPos+2]==5 and map[xPos+1][yPos+2]==0)
                        ||(map[xPos][yPos+2]==0 and map[xPos+1][yPos+2]==5)
                        ||(map[xPos][yPos+2]==5 and map[xPos+1][yPos+2]==5)){
                    emit motion(s, true, id);
                    return;
                }
                else{
                    break;
                }
            }
        }
        break;
    case 'L':
        if(side!='R'){
            if(xPos==0){
               break;
            }
            else{
                if((map[xPos-1][yPos]==0 and map[xPos-1][yPos+1]==0)
                        ||(map[xPos-1][yPos]==5 and map[xPos-1][yPos+1]==0)
                        ||(map[xPos-1][yPos]==0 and map[xPos-1][yPos+1]==5)
                        ||(map[xPos-1][yPos]==5 and map[xPos-1][yPos+1]==5)){
                    emit motion(s, true, id);
                    return;
                }
                else{
                    break;
                }
            }

        }
        break;
    case 'U':
        if(side!='D'){
            if(yPos==0){
                break;
            }
            else{
                if((map[xPos][yPos-1]==0 and map[xPos+1][yPos-1]==0)
                        ||(map[xPos][yPos-1]==5 and map[xPos+1][yPos-1]==0)
                        ||(map[xPos][yPos-1]==0 and map[xPos+1][yPos-1]==5)
                        ||(map[xPos][yPos-1]==5 and map[xPos+1][yPos-1]==5)){
                    emit motion(s, true, id);
                    return;
                }
                else{
                    break;

                }
            }

        }
        break;
    case 'R':
        if(side!='L'){
            if(xPos==24){
                break;
            }
            else{
                if((map[xPos+2][yPos]==0 and map[xPos+2][yPos+1]==0)
                        ||(map[xPos][yPos-1]==0 and map[xPos+1][yPos-1]==5)
                        ||(map[xPos][yPos-1]==5 and map[xPos+1][yPos-1]==0)
                        ||(map[xPos][yPos-1]==5 and map[xPos+1][yPos-1]==5)){
                    emit motion(s, true, id);
                    return;
                }
                else{
                    break;
                }
            }

        }
        break;
    default:
        break;
    }

    switch (side) {
    case 'D':
        if(yPos==24){
            emit motion('U', true, id);
        }
        else{
            if((map[xPos][yPos+2]==0 and map[xPos+1][yPos+2]==0)
                    ||(map[xPos][yPos+2]==5 and map[xPos+1][yPos+2]==0)
                    ||(map[xPos][yPos+2]==0 and map[xPos+1][yPos+2]==5)
                    ||(map[xPos][yPos+2]==5 and map[xPos+1][yPos+2]==5)){
                emit motion(side, true, id);
            }
            else{
                emit motion('U', true, id);
            }
        }
        break;
    case 'L':
        if(xPos==0){
            emit motion('R', true, id);
        }
        else{
            if((map[xPos-1][yPos]==0 and map[xPos-1][yPos+1]==0)
                    ||(map[xPos-1][yPos]==5 and map[xPos-1][yPos+1]==0)
                    ||(map[xPos-1][yPos]==0 and map[xPos-1][yPos+1]==5)
                    ||(map[xPos-1][yPos]==5 and map[xPos-1][yPos+1]==5)){
                emit motion(side, true, id);
            }
            else{
                emit motion('R', true, id);
            }
        }
        break;
    case 'U':
        if(yPos==0){
            emit motion('D', true, id);
        }
        else{
            if((map[xPos][yPos-1]==0 and map[xPos+1][yPos-1]==0)
                    ||(map[xPos][yPos-1]==5 and map[xPos+1][yPos-1]==0)
                    ||(map[xPos][yPos-1]==0 and map[xPos+1][yPos-1]==5)
                    ||(map[xPos][yPos-1]==5 and map[xPos+1][yPos-1]==5)){
                emit motion(side, true, id);
            }
            else{
                emit motion('D', true, id);
            }
        }
        break;
    case 'R':
        if(xPos==24){
            emit motion('L', true, id);
        }
        else{
            if((map[xPos+2][yPos]==0 and map[xPos+2][yPos+1]==0)
                    ||(map[xPos+2][yPos]==5 and map[xPos+2][yPos+1]==0)
                    ||(map[xPos+2][yPos]==0 and map[xPos+2][yPos+1]==5)
                    ||(map[xPos+2][yPos]==5 and map[xPos+2][yPos+1]==5)){
                emit motion(side, true, id);
            }
            else{
               emit motion('L', true, id);
            }
        }
        break;
    default:
        break;
    }



}

void GameMap::changeCoord(int xPos, int yPos, char side, int id)
{
    switch (side) {
    case 'D':
        map[xPos][yPos]=0;
        map[xPos+1][yPos]=0;
        map[xPos][yPos+2]=9;
        map[xPos+1][yPos+2]=9;
        break;
    case 'L':
        map[xPos+1][yPos]=0;
        map[xPos+1][yPos+1]=0;
        map[xPos-1][yPos]=9;
        map[xPos-1][yPos+1]=9;
        break;
    case 'U':
        map[xPos][yPos+1]=0;
        map[xPos+1][yPos+1]=0;
        map[xPos][yPos-1]=9;
        map[xPos+1][yPos-1]=9;
        break;
    case 'R':
        map[xPos][yPos]=0;
        map[xPos][yPos+1]=0;
        map[xPos+2][yPos]=9;
        map[xPos+2][yPos+1]=9;
        break;
    default:
        break;
    }
}

void GameMap::checkPlayerCoord(int xPos, int yPos, int direction, bool &tmp)
{

    switch(direction){
    case Qt::Key_Up:
        if(yPos == 0){
            tmp = false;
            return;
        }
        if((map[xPos][yPos-1] == 0 or map[xPos][yPos-1] == 5)and
           (map[xPos+1][yPos-1] == 0 or map[xPos+1][yPos-1] == 5)){
            tmp = true;
            return;
        }
        break;
    case Qt::Key_Down:
        if(yPos == 24){
            tmp = false;
            return;
        }
        if((map[xPos][yPos+2] == 0 or map[xPos][yPos+2] == 5)and
           (map[xPos+1][yPos+2] == 0 or map[xPos+1][yPos+2] == 5)){
            tmp = true;
            return;
        }
        break;
    case Qt::Key_Left:
        if(xPos == 0){
            tmp = false;
            return;
        }
        if((map[xPos-1][yPos] == 0 or map[xPos-1][yPos] == 5)and
           (map[xPos-1][yPos+1] == 0 or map[xPos-1][yPos+1] == 5)){
            tmp = true;
            return;
        }
        break;
    case Qt::Key_Right:
        if(xPos == 24){
            tmp = false;
            return;
        }
        if((map[xPos+2][yPos] == 0 or map[xPos+2][yPos] == 5)and
           (map[xPos+2][yPos+1] == 0 or map[xPos+2][yPos+1] == 5)){
            tmp = true;
            return;
        }
        break;
    }
    tmp = false;

}

void GameMap::spawnStars()
{
    stars->stop();
    stars->start(10000);
    int randBonus = qrand()%6;
    int xPos= qrand()%384;
    int yPos= qrand()%384;
    Stars *star = new Stars(xPos,yPos,this);
    Helmet *helmet = new Helmet(xPos,yPos,this);
    Pistol *pistol = new Pistol(xPos,yPos,this);
    Shovel *shovel = new Shovel(xPos,yPos,this);
    Granade *granade = new Granade(xPos,yPos,this);
    Health *health = new Health(xPos,yPos,this);
    switch (randBonus) {
    case 0:
        workScene->addItem(star);
        break;
    case 1:
        workScene->addItem(helmet);
        break;
    case 2:
        workScene->addItem(pistol);
        break;
    case 3:
        workScene->addItem(shovel);
        break;
    case 4:
        workScene->addItem(granade);
        break;
    case 5:
        workScene->addItem(health);
    default:
        break;
    }

}

void GameMap::spawnBullet(int xPos,int yPos, char side, int stars, int id)
{
    bool insrt=true;
    if(!bullerId->isEmpty()){
        for(int i=0;i<bullerId->size();i++){
            if(bullerId->at(i)==id){
                insrt=false;
            }
        }
    }
    if(insrt){
        bullerId->push_back(id);
        Bullet *bullet = new Bullet(xPos,yPos,side,stars,id,this);
        workScene->addItem(bullet);
        connect(bullet,SIGNAL(spawnExplosion(int,int,bool)),this,SLOT(spawnExplosion(int,int,bool)));
        connect(bullet,SIGNAL(CheckShield()),this,SLOT(CheckShieldSlot()));
        connect(bullet,SIGNAL(killBase()),this,SLOT(killBase()));
        connect(bullet,SIGNAL(enemyListing(QVector<Enemy*>*)),this,SLOT(enemyListing(QVector<Enemy*>*)));
        connect(bullet,SIGNAL(changeHealth(int)),this,SLOT(chengeHealthSlot(int)));
        connect(bullet,SIGNAL(delBullet(int)),this,SLOT(delBullet(int)));
        connect(this,SIGNAL(pause()),bullet,SLOT(pause()));
        connect(this,SIGNAL(start()),bullet,SLOT(start()));
    }


}

void GameMap::loadMap()
{
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    QFile file(":/maps/1.txt");
    file.open(QIODevice::ReadOnly);
    QString tmp;
    QTextStream in(&file);
    for(int y = 0; y < 26; y++)
        for(int x = 0; x < 26; x++){
            in >> tmp;
            if(tmp.toInt() == 1 and tmp.toInt() != map[x][y])
                this->createPlayer(x, y);
            if(tmp.toInt() == 7 and tmp.toInt() != map[x][y])
                this->createBase(x,y);
            if(tmp.toInt() != map[x][y])
                map[x][y] = tmp.toInt();
            if(tmp.toInt()!=0){
                createBlock(x,y,tmp.toInt());
            }
        }


    timerShovel = new QTimer(this);
    connect(timerShovel,SIGNAL(timeout()),this,SLOT(deleteShovel()));
    stars = new QTimer(this);
    connect(stars,SIGNAL(timeout()),this,SLOT(spawnStars()));
    blinkTimer = new QTimer(this);
    connect(blinkTimer, SIGNAL(timeout()),this,SLOT(spawnBlink()));
    blinkTimer->start(5000);
    stars->start(10000);

}

void GameMap::end()
{
    GameOver *gameover = new GameOver(176,416,this);
    workScene->addItem(gameover);
    emit pause();
    saveStars=stars->remainingTime();
    saveBlinkTimer=blinkTimer->remainingTime();
    stars->stop();
    blinkTimer->stop();
}

void GameMap::loadEnemys()
{
    QFile file(":/maps/1e.txt");
    file.open(QIODevice::ReadOnly);
    QString tmp;
    QTextStream in(&file);
    for(int i = 0; i < 20; i++){
        in >> tmp;
        enemyQueue.push_back(tmp.toInt());
    }
}

#include "game.h"

Game::Game()
{
    //Create main game scene
    QGraphicsScene *gameScene = new QGraphicsScene(this);

    //Create game screen, off scroll bars, show screen
    QGraphicsView *gameScreen = new QGraphicsView(gameScene);
    gameScreen->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameScreen->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    gameScreen->show();
    gameScene->setBackgroundBrush(QColor(99,99,99));

    //set screen and scene size
    gameScreen->setFixedSize(516,436);
    gameScene->setSceneRect(35, 0, 416, 416);
    QGraphicsRectItem *field = new QGraphicsRectItem(NULL);
    field->setRect(0,0,416,416);
    field->setPos(0,0);
    field->setBrush(Qt::black);
    gameScene->addItem(field);
    //Create game map
    map = new GameMap(gameScene);

}

void Game::gameEnd()
{
    points=map->getPoints();
    delete map;
}



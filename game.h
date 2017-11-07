#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include "gamemap.h"

class Game : public QObject
{
    Q_OBJECT
public:
    Game();
private:
    GameMap *map;
    int points;
public slots:
    void gameEnd();
};

#endif // GAME_H

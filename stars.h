#ifndef STARS_H
#define STARS_H

#include <QGraphicsRectItem>
#include <QPainter>

class Stars: public QObject, public QGraphicsRectItem
{
    Q_OBJECT
private:
public:
    explicit Stars(int xPos, int yPos, QObject *parent = 0);

signals:

public slots:
};

#endif // STARS_H

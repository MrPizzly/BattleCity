#ifndef HEALTHPANEL_H
#define HEALTHPANEL_H

#include <QGraphicsRectItem>
#include <QPainter>

class HealthPanel : public QObject, public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit HealthPanel(int xPos, int yPos, QObject *parent = 0);
public slots:
    void changeHealth(int count);
};

#endif // HEALTHPANEL_H

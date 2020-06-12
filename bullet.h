#ifndef BULLET_H
#define BULLET_H

#include <QObject>
#include <QGraphicsPixmapItem>
#include <QGraphicsScene>

class bullet : public QObject, public QGraphicsPixmapItem
{
    Q_OBJECT
public:
    bullet(double, double, double, double);
    void set_bomb(double, double, double, double);
    bool colliding_with_bomb();

public slots:
    void fly();

signals:
    void explode();

private:
    double bomb_x, bomb_y, bomb_w, bomb_h;
};

#endif // BULLET_H

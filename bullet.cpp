#include "bullet.h"

bullet::bullet(double init_bomb_x, double init_bomb_y, double init_bomb_w, double init_bomb_h)
{
    bomb_x = init_bomb_x;
    bomb_y = init_bomb_y;
    bomb_w = init_bomb_w;
    bomb_h = init_bomb_h;
}

void bullet::fly()
{
    setPos(x(), y() - 5);
    if(colliding_with_bomb())
    {
        emit explode();
        this->scene()->removeItem(this);
        delete this;
    }
    if(y() + 178 < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

void bullet::rm_bullet()
{
    this->scene()->removeItem(this);
    delete this;
}

void bullet::set_bomb(double init_bomb_x, double init_bomb_y, double init_bomb_w, double init_bomb_h)
{
    bomb_x = init_bomb_x;
    bomb_y = init_bomb_y;
    bomb_w = init_bomb_w;
    bomb_h = init_bomb_h;
}

bool bullet::colliding_with_bomb()
{
    return this->x() + this->pixmap().width() >= bomb_x && this->x() <= bomb_x + bomb_w && this->y() + this->pixmap().height() >= bomb_y && this->y() <= bomb_y + bomb_h;
}

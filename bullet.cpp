#include "bullet.h"

bullet::bullet()
{

}

void bullet::fly()
{
    setPos(x(), y() - 8);
    if(y() + 178 < 0) {
        this->scene()->removeItem(this);
        delete this;
    }
}

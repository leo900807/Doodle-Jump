#ifndef PLATFORM_BASE_H
#define PLATFORM_BASE_H

#include <QGraphicsPixmapItem>

class platform_base : public QGraphicsPixmapItem
{
public:
    platform_base();
    virtual bool be_jumped() = 0;
};

#endif // PLATFORM_BASE_H

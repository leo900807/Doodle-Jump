#ifndef PLATFORM_H
#define PLATFORM_H

#include <QGraphicsScene>
#include "platform_base.h"

class normal_platform : public platform_base
{
public:
    normal_platform();
    normal_platform(double, double);
    virtual bool be_jumped();
};

class fragile_platform : public platform_base
{
public:
    fragile_platform();
    fragile_platform(double, double);
    virtual bool be_jumped();
};

#endif // PLATFORM_H

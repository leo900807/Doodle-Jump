#include "platform.h"
#include <QDebug>

normal_platform::normal_platform() : platform_base()
{
    setPos(0, 0);
    setPixmap(QPixmap(":/res/normal_platform.png").scaled(100, 30));
}

normal_platform::normal_platform(double init_xx, double init_yy) : platform_base()
{
    setPos(init_xx, init_yy);
    setPixmap(QPixmap(":/res/normal_platform.png").scaled(100, 30));
}

bool normal_platform::be_jumped()
{
    return 0;
}

fragile_platform::fragile_platform() : platform_base()
{
    setPos(0, 0);
    setPixmap(QPixmap(":/res/fragile_platform.png").scaled(100, 30));
}

fragile_platform::fragile_platform(double init_xx, double init_yy) : platform_base()
{
    setPos(init_xx, init_yy);
    setPixmap(QPixmap(":/res/fragile_platform.png").scaled(100, 30));
}

bool fragile_platform::be_jumped()
{
    this->scene()->removeItem(this);
    delete this;
    return 1;
}

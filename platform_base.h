#ifndef PLATFORM_BASE_H
#define PLATFORM_BASE_H

class platform_base
{
public:
    platform_base(int, int);
    virtual ~platform_base();

private:
    int x, y;
};

#endif // PLATFORM_BASE_H

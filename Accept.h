#ifndef ACCEPT_H
#define ACCEPT_H
#include "IComp.h"

class IShow
{
    virtual void show()=0;
};

class IHuman:public IShow
{
public:
    IHuman(){};
    virtual void show() {};
};

class IDepart:public IShow
{
public:
    IDepart(){};
    virtual void show() {};
};

class ICenter:public IShow
{
public:
    ICenter(){};
    virtual void show() {};
};


#endif // ACCEPT_H

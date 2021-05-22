#ifndef ACCEPT_H
#define ACCEPT_H
class IComp;
#include <qtextbrowser.h>
class IShow
{
    virtual void show(IComp *, QTextBrowser*)=0;
};

class IHuman:public IShow
{
public:
    IHuman(){};
    virtual void show(IComp *, QTextBrowser*) override;

};

class IDepart:public IShow
{
public:
    IDepart(){};
    virtual void show(IComp * depart, QTextBrowser*) override;

};

class ICenter:public IShow
{
public:
    ICenter(){};
    virtual void show(IComp *, QTextBrowser*) override;
};


#endif // ACCEPT_H

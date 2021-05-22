#ifndef ACCEPT_H
#define ACCEPT_H
class IComp;
#include "dialog.h"
#include <qtextbrowser.h>
class IShow
{
public:
    virtual void show(IComp *, QTextBrowser*)=0;
    virtual void showForm(IComp *,Dialog*)           =0;
};

class IHuman:public IShow
{
public:
    IHuman(){};
    virtual void show(IComp *, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
};

class IDepart:public IShow
{
public:
    IDepart(){};
    virtual void show(IComp * depart, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
};

class ICenter:public IShow
{
public:
    ICenter(){};
    virtual void show(IComp *, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
};


#endif // ACCEPT_H

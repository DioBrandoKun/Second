#ifndef ACCEPT_H
#define ACCEPT_H
class IComp;
#include "dialog.h"
#include <qtextbrowser.h>
class IShow
{
public:
    virtual void show(IComp *, QTextBrowser*)        =0;
    virtual void showForm(IComp *,Dialog*)           =0;
    virtual void showReadForm(IComp *,Dialog*)       =0;
    virtual void changeData(IComp *, QStringList)    =0;
    virtual void addClick(IComp *, QStringList)      =0;
};

class IHuman:public IShow
{
public:
    IHuman(){};
    virtual void show(IComp *, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
    virtual void showReadForm(IComp *,Dialog*) override;
    virtual void changeData(IComp *, QStringList) override;
    virtual void addClick(IComp *, QStringList)  override;
};

class IDepart:public IShow
{
public:
    IDepart(){};
    virtual void show(IComp * depart, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
    virtual void showReadForm(IComp *,Dialog*) override;
    virtual void changeData(IComp *, QStringList) override;
    virtual void addClick(IComp *, QStringList)  override;
};

class ICenter:public IShow
{
public:
    ICenter(){};
    virtual void show(IComp *, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
    virtual void showReadForm(IComp *,Dialog*) override;
    virtual void changeData(IComp *, QStringList) override;
    virtual void addClick(IComp *, QStringList)  override;
};


#endif // ACCEPT_H

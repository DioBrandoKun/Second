#ifndef ACCEPT_H
#define ACCEPT_H
class IComp;
#include "dialog.h"
#include <qtextbrowser.h>
class IShow                                             //Интерфейс из группы стратегии для реализации поведения
{
public:
    //Отвечает за отображении информации в правом окошке
    //@IComp ссылка на элемент
    //@QTextBrowser ссылка на окошко
    virtual void show(IComp *, QTextBrowser*)        =0;

    //Отвечает за отображении формы с информацией
    //@IComp ссылка на элемент
    //@Dialog ссылка на элемент форомчки
    virtual void showForm(IComp *,Dialog*)           =0;

    //Отвечает за отображении формы для добавления элемента
    //@IComp ссылка на элемент
    //@Dialog ссылка на элемент форомчки
    virtual void showReadForm(Dialog*)       =0;

    //Отвечает за изменение информации элемента
    //@IComp ссылка на элемент
    //@QStringList список новых данных
    virtual void changeData(IComp *, QStringList)    =0;

    //Отвечает за создание нового элемента
    //@IComp ссылка на родительский элемент
    //@QStringList список данных для нового элемента
    virtual void addClick(IComp *, QStringList)      =0;

    //Отвечает за сохранение в xml
    //@IComp ссылка на объект
    //@QString out результат XML данных
    //@shift сдвиг табуляций
    virtual void wrieXML(IComp *,QString& out,QString shift) =0;

    virtual ~IShow()                                 {};
};

class IHuman:public IShow
{
public:
    IHuman(){};
    virtual void show(IComp *, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
    virtual void showReadForm(Dialog*) override;
    virtual void changeData(IComp *, QStringList) override;
    virtual void addClick(IComp *, QStringList)  override;
    virtual void wrieXML(IComp *,QString& out,QString shift) override;
    virtual ~IHuman() {};
};

class IDepart:public IShow
{
public:
    IDepart(){};
    virtual void show(IComp * depart, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
    virtual void showReadForm(Dialog*) override;
    virtual void changeData(IComp *, QStringList) override;
    virtual void addClick(IComp *, QStringList)  override;
    virtual void wrieXML(IComp *,QString& out,QString shift) override;
    virtual ~IDepart() {};
};

class ICenter:public IShow
{
public:
    ICenter(){};
    virtual void show(IComp *, QTextBrowser*) override;
    virtual void showForm(IComp *,Dialog*) override;
    virtual void showReadForm(Dialog*) override;
    virtual void changeData(IComp *, QStringList) override;
    virtual void addClick(IComp *, QStringList)  override;
    virtual void wrieXML(IComp *,QString& out,QString shift) override;
    virtual ~ICenter() {};
};


#endif // ACCEPT_H

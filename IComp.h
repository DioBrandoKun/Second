#ifndef ICOMP_H
#define ICOMP_H
#include "Accept.h"
#include <iostream>
#include <QString>
#include <vector>
#include <QTreeWidgetItem>
#include <qDebug>
#include "ICounter.h"
class IComp
{
public:
    IComp(IShow* show):m_show(show){};
    IShow* m_show;                      //Поведение вспомогательного окна
    IComp* m_father=nullptr;
    virtual void accept(ICounter*)          =0;
    virtual void remove()                   =0;
    virtual void remove(IComp*)             =0;
    virtual void tree(std::vector<std::pair<int,QTreeWidgetItem*>>&,
                      QMap<QTreeWidgetItem*,IComp*>& m_pointer
                      ,int num=0)           =0;
    virtual ~IComp()                        {};
    virtual void out()                      =0;
    void Show(Dialog* window)
    {
        m_show->showForm(this,window);
    }
    void Chage(QStringList change)
    {
        m_show->changeData(this,change);
    }
    void showReadForm(Dialog* window)
    {
        m_show->showReadForm(this,window);
    }
    void Add(QStringList list)
    {
        m_show->addClick(this,list);
    }

};

struct Initials
{
    QString Name;
    QString Ser;
    QString Pat;
    Initials(QString& name, QString& ser, QString& pat)
    {
        Name=name;
        Ser=ser;
        Pat=pat;
    }
    Initials(){};
};

class Human:public IComp
{
public:
    Initials    m_init;     //Инициалы
    QString     m_pos;      //Должность
    long        m_salary;   //Зарплата
    Human(QString& name,QString& ser,
          QString& pat, QString& pos,
          QString& salary,
          IShow* hum=new IHuman):IComp(hum), m_init(name,ser,pat),
                                  m_pos(pos)
    {
        m_salary = salary.toLong();
    }
    virtual ~Human()
    {
        m_pos        =   nullptr;
        m_init.Name  =   nullptr;
        m_init.Ser   =   nullptr;
        m_init.Pat   =   nullptr;
    }
    void remove()  override
    {
        m_father->remove(this);
        this->~Human();
    }
    void remove(IComp* newElem) override
    {

    }
    virtual void tree(std::vector<std::pair<int,QTreeWidgetItem*>>& out,
                      QMap<QTreeWidgetItem*,IComp*>& m_pointer
                      ,int num=0) override
    {
        QTreeWidgetItem* item=new QTreeWidgetItem();//m_tree
        item->setText(num,m_init.Name);
        //ProperItem* transform=(ProperItem*) item;
        //transform->SetData(this);
        m_pointer.insert(item,this);
        out.push_back({num,item});
    }
    virtual void out() override
    {
        #include <QDebug>
        qDebug()<<m_init.Name;
    }
    virtual void accept(ICounter* counter) override
    {
       counter->Count(this);
    }
    QStringList GetData()
    {
        return {m_init.Name,m_init.Ser,m_init.Pat,m_pos,QString::number(m_salary)};
    }
};


class Departament:public IComp
{
public:
    QString     m_name;                 //Название
    bool        m_removed=false;        //Условие удаленности, пришлось добавить для основного офиса
    std::vector<IComp*> m_elemnts;
    Departament(QString& name,
                IShow* depart= new IDepart):IComp(depart), m_name(name)
    {
    }

    void add(IComp* newElem)
    {
        newElem->m_father=this;
        m_elemnts.push_back(newElem);
    }
    virtual ~Departament()
    {
        m_name    = nullptr;
    }
    void remove()  override
    {
        m_removed=true;
        for(int i=0;i<m_elemnts.size();i++)
        {
            m_elemnts[i]->remove();
        }
        if(m_father!=nullptr)
            m_father->remove(this);
    }
    void remove(IComp* newElem) override
    {
        auto remove_iter=std::remove(m_elemnts.begin(),m_elemnts.end(),newElem);    //Вот тут может неправильно удалять
        m_elemnts.erase(remove_iter,m_elemnts.end());
    }
    virtual void tree(std::vector<std::pair<int,QTreeWidgetItem*>>& out,
                      QMap<QTreeWidgetItem*,IComp*>& m_pointer
                      ,int num=0) override
    {
        QTreeWidgetItem* item=new QTreeWidgetItem();
        item->setText(num,m_name);
        //ProperItem* transform=(ProperItem*) item;
        //transform->SetData(this);
        m_pointer.insert(item,this);
        out.push_back({num,item});
        for(auto* elems:m_elemnts)
        {
            elems->tree(out,m_pointer,num+1);
        }
    }
    virtual void accept(ICounter* counter) override
    {
        counter->Count(this);
        for(auto* elems:m_elemnts)
        {
            elems->accept(counter);
        }
    }
    virtual void out() override
    {

        qDebug()<<m_name;
        for(auto* elems:m_elemnts)
        {
            elems->out();
        }
    }
    QString GetName() {return m_name;}
};

#endif // ICOMP_H

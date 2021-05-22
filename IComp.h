#ifndef ICOMP_H
#define ICOMP_H
#include "Accept.h"
#include <iostream>
#include <QString>
#include <vector>
#include <qDebug>
#include "ProperItem.h"

class IComp
{
public:
    IComp(IShow* show):m_show(show){};
    IShow* m_show;                      //Поведение вспомогательного окна
    IComp* m_father=nullptr;
    virtual void add(IComp*)                =0;
    virtual void remove()                   =0;
    virtual void remove(IComp*)             =0;
    virtual void tree(std::vector<std::pair<int,ProperItem*>>&, int num=0)           =0;
    virtual ~IComp()                        {};
    virtual void out()                      =0;
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
    void add(IComp* newElem)  override
    {

    }
    void remove(IComp* newElem) override
    {

    }
    virtual void tree(std::vector<std::pair<int,ProperItem*>>& out, int num=0) override
    {
        QTreeWidgetItem* item=new QTreeWidgetItem();//m_tree
        item->setText(num,m_init.Name);
        ProperItem* transform=(ProperItem*) item;
        transform->SetData(this);
        out.push_back({num,transform});
    }
    virtual void out() override
    {
        #include <QDebug>
        qDebug()<<m_init.Name;
    }
};


class Departament:public IComp
{
public:
    QString     m_name;   //Название
    int         m_num;    //Количество сотрудников
    double      m_salary; //Средняя зарплата
    std::vector<IComp*> m_elemnts;
    Departament(QString& name,
                IShow* depart= new IDepart):IComp(depart), m_name(name)
    {
    }

    void add(IComp* newElem)  override
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
        for(int i=0;i<m_elemnts.size();i++)
        {
            m_elemnts[i]->remove();
        }
        if(m_father!=nullptr)
            m_father->remove(this);
        this->~Departament();
    }
    void remove(IComp* newElem) override
    {
        auto remove_iter=std::remove(m_elemnts.begin(),m_elemnts.end(),newElem);    //Вот тут может неправильно удалять
        m_elemnts.erase(remove_iter,m_elemnts.end());
    }
    virtual void tree(std::vector<std::pair<int,ProperItem*>>& out, int num=0) override
    {
        QTreeWidgetItem* item=new QTreeWidgetItem();
        item->setText(num,m_name);
        ProperItem* transform=(ProperItem*) item;
        transform->SetData(this);
        out.push_back({num,transform});
        for(auto* elems:m_elemnts)
        {
            elems->tree(out,num+1);
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
};

#endif // ICOMP_H

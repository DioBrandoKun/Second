#ifndef ICOMP_H
#define ICOMP_H
#include "Accept.h"
#include <iostream>
#include <QString>
#include <vector>
class IComp
{
public:
    IComp(IShow* show):m_show(show){};
    IShow* m_show;                      //Поведение вспомогательного окна
    virtual void add(IComp*)      =0;
    virtual void remove(IComp*)   =0;
    virtual void tree()           =0;
};

struct Initials
{
    std::string Name;
    std::string Ser;
    std::string Pat;
    Initials(std::string& name, std::string& ser, std::string& pat)
    {
        Name=name;
        Ser=ser;
        Pat=pat;
    }
    Initials(){};
};

class Human:public IComp
{
    Initials    m_init;     //Инициалы
    std::string m_pos;      //Должность
    long        m_salary;   //Зарплата
    Human(std::string& name,std::string& ser,
          std::string& pat, std::string& pos,
          std::string& salary,
          IShow* hum=new IHuman):IComp(hum), m_init(name,ser,pat),
                                  m_pos(pos)
    {
        QString help = QString::fromStdString(salary);
        m_salary = help.toLong();
    }
};


class Departament:IComp
{
public:
    std::string m_name;   //Название
    int         m_num;    //Количество сотрудников
    double      m_salary; //Средняя зарплата
    std::vector<IComp*> m_elemnts;
    Departament(std::string& name, std::string& num, std::string& salary,
                IShow* depart= new IDepart):IComp(depart), m_name(name)
    {
        QString numS = QString::fromStdString(num);
        QString salaryS = QString::fromStdString(salary);
        m_num = numS.toInt();
        m_salary = salaryS.toDouble();
    }

    void add(IComp* newElem)  override
    {
        m_elemnts.push_back(newElem);
    }

    void remove(IComp* newElem)  override
    {
        auto remove_iter=std::remove(m_elemnts.begin(),m_elemnts.end(),newElem);    //Вот тут может неправильно удалять
        m_elemnts.erase(remove_iter,m_elemnts.end());
        m_elemnts.shrink_to_fit();
    }
};

#endif // ICOMP_H

#ifndef ICOUNTER_H
#define ICOUNTER_H
class Departament;
class Human;


class ICounter//Посетитель для подразделений
{

public:
    virtual void Count(Departament*)=0;

    virtual void Count(Human* obj)=0;
};

class InfoView:public ICounter
{
    int         m_num       =0; //Считает кол-во сотрудников
    double      all_salary  =0; //Считает всю зарплату
    int         m_dep       =0; //Считает кол-во отделов
public:
    InfoView(){};
    virtual void Count(Departament*);

    virtual void Count(Human* obj);

    int  GetDep(){return m_dep;}
    int  GetCount(){return m_num;}
    double GetMid(){return all_salary/m_num;}
};

#endif // ICOUNTER_H

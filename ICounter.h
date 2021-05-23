#ifndef ICOUNTER_H
#define ICOUNTER_H
class Departament;
class Human;


class ICounter                  //Посетитель для элементов
{

public:
    virtual void Count(Departament*)=0;

    virtual void Count(Human* obj)=0;
};

class InfoView:public ICounter
{
    int         m_num       =0; //Кол-во сотрудников
    double      all_salary  =0; //Вся зарплата для отдела
    int         m_dep       =0; //Кол-во отделов
public:
    InfoView(){};
    //Считает количество департаментов
    virtual void Count(Departament*);

    //Считает количество людей и их зарплату
    virtual void Count(Human* obj);

    //Возвращает число департаментов
    int  GetDep(){return m_dep;}
    //Возвращает число людей
    int  GetCount(){return m_num;}
    //Возвращает среднюю зарплату
    double GetMid(){return all_salary/m_num;}
};

#endif // ICOUNTER_H

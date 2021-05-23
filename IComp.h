#ifndef ICOMP_H
#define ICOMP_H
#include "Accept.h"
#include <iostream>
#include <QString>
#include <vector>
#include <QTreeWidgetItem>
#include <qDebug>
#include "ICounter.h"
class IComp                             //Абстрактный класс для паттерна компановщик
{
public:
    IComp(IShow* show):m_show(show){};
    IShow* m_show;                      //Вспомогательное поведение
    IComp* m_father=nullptr;            //В отличии от стандартного компановщика, хранит ссылку на отца

    //Метод для посетителя
    //@ICounter посетитель
    virtual void accept(ICounter*)          =0;

    //Метод удаления элемента
    virtual void remove()                   =0;

    //Метод удаленния определенного элемента
    virtual void remove(IComp*)             =0;

    //Метод построения дерева
    //Каждый элемент создает свое представление QTreeWidgetItem
    //@std::vector<std::pair<int,QTreeWidgetItem*>> сохраняет отклонение элемента и его представление
    //@QMap<QTreeWidgetItem*,IComp*> сохраняет ссылку для отображения элемента на его данные
    virtual void tree(std::vector<std::pair<int,QTreeWidgetItem*>>&,
                      QMap<QTreeWidgetItem*,IComp*>& m_pointer
                      ,int& size, int num=0)           =0;
    virtual ~IComp()                        {};

    //Метод для создания копии
    //@IComp копирующий элемент
    //@root для создания одного интерфейса ICenter
    virtual void clone(IComp* evm,bool root=false)          =0;

    //Метод для вывода в консоль
    virtual void out()                      =0;

    //Метод для отображения формы
    void Show(Dialog* window)
    {
        m_show->showForm(this,window);
    }

    //Метод для изменнения данных объекта
    void Chage(QStringList change)
    {
        m_show->changeData(this,change);
    }

    //Метод для создания формы для добавления к объекту
    void showReadForm(Dialog* window)
    {
        m_show->showReadForm(this,window);
    }

    //Метод для добавления элемента
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




class Departament:public IComp
{
public:
    QString     m_name;                 //Название
    bool        m_removed=false;        //Условие удаленности, пришлось добавить для проверки данных
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
        m_elemnts.erase(m_elemnts.begin(),m_elemnts.end());
        if(m_father!=nullptr)
            m_father->remove(this);
    }
    void remove(IComp* newElem) override
    {
        auto remove_iter=std::remove(m_elemnts.begin(),m_elemnts.end(),newElem);
        if( remove_iter!= m_elemnts.end())
        m_elemnts.erase(remove_iter,m_elemnts.end());
    }
    virtual void tree(std::vector<std::pair<int,QTreeWidgetItem*>>& out,
                      QMap<QTreeWidgetItem*,IComp*>& m_pointer
                      ,int& size,int num=0) override
    {
        if(num>size) size=num;
        QTreeWidgetItem* item=new QTreeWidgetItem();
        item->setText(num,m_name);
        m_pointer.insert(item,this);
        out.push_back({num,item});
        for(auto* elems:m_elemnts)
        {
            elems->tree(out,m_pointer,size,num+1);
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
    virtual void clone(IComp* evm, bool root=false) override
    {
        if(root)
        {
            for(auto* elems:m_elemnts)
            {
                elems->clone(evm,false);
            }
        }
        else
        {
            IComp* item=new Departament(m_name);
            Departament* evm_iter= (Departament*) evm;
            evm_iter->add(item);
            for(auto* elems:m_elemnts)
            {
                elems->clone(item,false);
            }
        }

    }

    QString GetName() {return m_name;}
};

class Human:public IComp
{
public:
    friend IHuman;
    Initials    m_init;     //Инициалы
    QString     m_pos;      //Должность
    long        m_salary;   //Зарплата
    friend InfoView;


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
        m_father=nullptr;
        this->~Human();
    }
    void remove(IComp* newElem) override
    {

    }
    virtual void tree(std::vector<std::pair<int,QTreeWidgetItem*>>& out,
                      QMap<QTreeWidgetItem*,IComp*>& m_pointer
                      ,int& size,int num=0) override
    {
        if(num>size) size=num;
        QTreeWidgetItem* item=new QTreeWidgetItem();//m_tree
        item->setText(num,m_init.Name);
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
    virtual void clone(IComp* evm,bool root=false) override
    {
        Departament* evm_iter= (Departament*) evm;
        QString salar=QString::number(m_salary);
        Human* item = new Human(m_init.Name,
                                m_init.Ser,m_init.Pat,
                                m_pos,salar);
        evm_iter->add(item);
    }
};
#endif // ICOMP_H

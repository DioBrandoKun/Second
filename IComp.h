#ifndef ICOMP_H
#define ICOMP_H
#include "Accept.h"
#include <iostream>
#include <QString>
#include <vector>
#include <QTreeWidgetItem>
#include "ICounter.h"
class IComp                             //Абстрактный класс для паттерна компановщик
{
protected:
    IComp(IShow* show):m_show(show){};
    IShow* m_show;                      //Вспомогательное поведение
    IComp* m_father=nullptr;            //В отличии от стандартного компановщика, хранит ссылку на отца
public:
    //Метод добавления ссылки на родителя
    //@newFather новый родитель
    void SetFather(IComp* newFather)
    {
        m_father=newFather;
    }

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

    //Методы вывода информациии об объекте в доп окошко
    //@placeholder ссылка на окошко
    void ShowInfo(QTextBrowser* placeholder)
    {
        m_show->show(this,placeholder);
    }

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
        m_show->showReadForm(window);
    }

    //Метод для добавления элемента
    void Add(QStringList list)
    {
        m_show->addClick(this,list);
    }
    //Метод для вывод в XML формат
    void WriteXML(QString& out,QString shift)
    {
        m_show->wrieXML(this,out,shift);
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
    friend IDepart;
    friend ICenter;
    QString     m_name;                 //Название
    bool        m_removed=false;        //Условие удаленности, пришлось добавить для проверки данных
    std::vector<IComp*> m_elemnts;

    //Вызов ввода XML файл для всех потомков
    void wrieXMLall(QString &out, QString shift)
    {
        for(auto& item:m_elemnts)
            item->WriteXML(out,shift);
    }
public:
    Departament(QString& name,
                IShow* depart= new IDepart):IComp(depart), m_name(name)
    {
    }

    void add(IComp* newElem)
    {
        newElem->SetFather(this);
        m_elemnts.push_back(newElem);
    }
    virtual ~Departament()
    {
        for(unsigned i=0;i<m_elemnts.size();i++)
        {
           delete m_elemnts[i];
        }
        m_elemnts.erase(m_elemnts.begin(),m_elemnts.end());
        m_father  = nullptr;
        m_name    = nullptr;
        delete m_show;
    }
    void remove()  override
    {
        m_removed=true;
        if(m_father!=nullptr)
            m_father->remove(this);
    }

    void remove(IComp* newElem) override
    {
        auto remove_obj =std::find(m_elemnts.begin(),m_elemnts.end(),newElem);
        if( remove_obj!= m_elemnts.end())
        {
            m_elemnts.erase(remove_obj);
            m_elemnts.shrink_to_fit();
            delete newElem;
        }
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

    //Информация о данных данного класса
    bool Deleted() {return m_removed;}

    //Получение имени данного класса
    QString GetName() {return m_name;}

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

};

class Human:public IComp
{
    friend IHuman;
    friend InfoView;
    Initials    m_init;     //Инициалы
    QString     m_pos;      //Должность
    long        m_salary;   //Зарплата
public:

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
        m_father=nullptr;
        m_pos        =   nullptr;
        m_init.Name  =   nullptr;
        m_init.Ser   =   nullptr;
        m_init.Pat   =   nullptr;
        delete m_show;
    }
    void remove()  override
    {
        if(m_father!=nullptr)
            m_father->remove(this);
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

#include <IComp.h>
#include <Accept.h>
#include <ICounter.h>
#include "dialog.h"
void IHuman::show(IComp * obj, QTextBrowser * text)
{
    text->clear();

    text->append("Сотрудник:");
    Human* item=(Human*)obj;
    QString Output="Имя: " + item->m_init.Name;
    text->append(Output);
    Output="Фамилия: " + item->m_init.Ser;
    text->append(Output);
    Output="Отчество: " + item->m_init.Pat;
    text->append(Output);
    Output="Должность: " + item->m_pos;
    text->append(Output);
    Output="Зарплата: " + QString::number(item->m_salary);
    text->append(Output);
}

void IDepart::show(IComp * obj, QTextBrowser * text)
{
    text->clear();
    QString Output="Отдел:\n";
    Output ="<B>"+Output ;
    Departament* item=(Departament*)obj;

    text->append(Output);
    Output =item->m_name;

    InfoView* count=new InfoView();
    obj->accept(count);

    text->append(Output);
    Output ="Колличество сотрудников на данный момент:" + QString::number(count->GetCount());
    text->append(Output);
    Output ="Средняя зарплата:" + QString::number(count->GetMid());
    text->append(Output);

    delete count;
}

void ICenter::show(IComp * obj, QTextBrowser * text)
{
    text->clear();
    QString Output="Филиал: ";
    Output ="<B>"+Output ;
    Departament* item=(Departament*)obj;

    Output +=item->m_name;
    text->append(Output);

    InfoView* count=new InfoView();
    obj->accept(count);

    Output ="Количество отделов в фирме: " + QString::number(count->GetDep()-1);
    text->append("<B>"+Output);
    Output ="Колличество сотрудников в фирме: " + QString::number(count->GetCount());
    text->append("<B>"+Output);
    Output ="Средняя зарплата в фирме: " + QString::number(count->GetMid());
    text->append("<B>"+Output);

    delete count;

}

void IHuman::showForm(IComp *obj,Dialog* mainForm)
{
   Human* item = (Human*) obj;
   mainForm->HumanForm(item->GetData());
   mainForm->show();
}
void ICenter::showForm(IComp *obj,Dialog* mainForm)
{
    Departament* item=(Departament *) obj;
    mainForm->DepartForm(item->GetName());
    mainForm->show();
}
void IDepart::showForm(IComp *obj,Dialog* mainForm)
{
    Departament* item=(Departament *) obj;
    mainForm->DepartForm(item->GetName());
    mainForm->show();
}

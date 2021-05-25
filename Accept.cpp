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

void IHuman::changeData(IComp *obj, QStringList data)
{
    Human* item = (Human*) obj;
    if(data[0]=="" || data[1]=="")
        return;
    Initials new_init{data[0],data[1],data[2]};
    item->m_init=new_init;
    item->m_pos=data[3];
    item->m_salary=data[4].toLong();
}

void ICenter::changeData(IComp *obj, QStringList data)
{
    if(data[0]=="")
        return;
    Departament* item=(Departament *) obj;
    item->m_name=data[0];
}

void IDepart::changeData(IComp *obj, QStringList data)
{
    if(data[0]=="")
        return;
    Departament* item=(Departament *) obj;
    item->m_name=data[0];
}

void IHuman::showReadForm(Dialog* mainForm)
{
   mainForm->reject();
   return;
}
void ICenter::showReadForm(Dialog* mainForm)
{
    mainForm->SuperFormRead();
    mainForm->show();
}
void IDepart::showReadForm(Dialog* mainForm)
{
    mainForm->HumanFormRead();
    mainForm->show();
}

void IHuman::addClick(IComp *obj, QStringList data)
{
    return;
}

void ICenter::addClick(IComp *obj, QStringList data)
{
    Departament* item=(Departament *) obj;
    if(data[0]=="")
        return;

    if(data.size()>1)
    {
        if(data[0]=="" || data[1]=="")
            return;
        for(int i=1;i<4;i++)
        {
            if(data[i]=="")
                data[i]="Not stated";
        }
        if(data[4]=="")
            data[4]="0";
        Human* newbie = new Human(data[0],data[1],
                data[2],data[3],data[4]);
        item->add(newbie);
    }
    else
    {
        if(data[0]=="") return;
        Departament* newbie=new Departament(data[0]);
        item->add(newbie);
    }
}

void IDepart::addClick(IComp *obj, QStringList data)
{
    if(data[0]=="" || data[1]=="")
        return;
    for(int i=1;i<4;i++)
    {
        if(data[i]=="")
            data[i]="Not stated";
    }
    if(data[4]=="")
        data[4]="0";
    Departament* item=(Departament *) obj;
    Human* newbie = new Human(data[0],data[1],
            data[2],data[3],data[4]);
    item->add(newbie);
}
void IHuman::wrieXML(IComp * obj, QString &out, QString shift)
{
    Human* item = (Human*) obj;
    QString insideShift=shift+'\t';
    out+=shift+"<employment>"+'\n';
    out+=insideShift+"<surname>"+item->m_init.Ser+"</surname>"+'\n';
    out+=insideShift+"<name>"+item->m_init.Name+"</name>"+'\n';
    out+=insideShift+"<middleName>"+item->m_init.Pat+"</middleName>"+'\n';
    out+=insideShift+"<function>"+item->m_pos+"</function>"+'\n';
    out+=insideShift+"<salary>"+QString::number(item->m_salary)+"</salary>"+'\n';
    out+=shift+"</employment>"+'\n';
}

void IDepart::wrieXML(IComp *obj, QString &out, QString shift)
{
    Departament* item=(Departament *) obj;
    out+=shift+"<department name="+'"'+item->GetName()+'"'+">\n";
    out+=shift+'\t'+"<employments>\n";
    item->wrieXMLall(out,shift+'\t'+'\t');
    out+=shift+'\t'+"</employments>\n";
    out+=shift+"</department>\n";
}
void ICenter::wrieXML(IComp *obj, QString &out, QString shift)
{
    Departament* item=(Departament *) obj;
    out+="<departments>\n";
    item->wrieXMLall(out,shift+'\t');
    out+="</departments>";
}

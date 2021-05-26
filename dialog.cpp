#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}
bool Dialog::getData(QStringList& inp)
{
    QRegExp num("^[0-9]{1,}$");
    QRegExp word("^[а-яА-ЯёЁa-zA-Z]{1,}$");
    QRegExp wordSpace("^[а-яА-ЯёЁa-zA-Z ]{1,}$");
    QString name=ui->firstBody->toPlainText();
    QString ser=ui->secondBody->toPlainText();
    QString pat=ui->thirdBody->toPlainText();
    QString func=ui->foruthBody->toPlainText();
    QString salar=ui->fifthBody->toPlainText();

    //Человек
    if(!state)
    {

       bool out=   word.exactMatch(name)&&
                word.exactMatch(ser)&&
                word.exactMatch(pat)&&
                wordSpace.exactMatch(func)&&
                num.exactMatch(salar);
        inp=QStringList({name,ser,pat,func,salar});
        return out;
    }//Отдел
    else
    {
        inp=QStringList({name});
        bool out=   wordSpace.exactMatch(name);
        return out;
    }
}

void Dialog::HumanForm(QStringList list)
{

    HumanFormRead();
    ui->firstBody->setText(list[0]);
    ui->secondBody->setText(list[1]);
    ui->thirdBody->setText(list[2]);
    ui->foruthBody->setText(list[3]);
    ui->fifthBody->setText(list[4]);

}

void Dialog::DepartForm(QString name)
{

    DepartFormRead();
    ui->firstBody->setText(name);


}
void Dialog::HumanFormRead()
{
    state=0;
    ui->first->setText("Имя");
    ui->second->setText("Фамилия");
    ui->third->setText("Отчество");
    ui->fourth->setText("Должность");
    ui->fifth->setText("Зарплата");

    ui->second->show();
    ui->third->show();
    ui->fourth->show();
    ui->fifth->show();

    ui->secondBody->show();
    ui->thirdBody->show();
    ui->foruthBody->show();
    ui->fifthBody->show();
}

void Dialog::DepartFormRead()
{
    state=1;
    ui->first->setText("Название");
    ui->second->hide();
    ui->third->hide();
    ui->fourth->hide();
    ui->fifth->hide();

    ui->secondBody->hide();
    ui->thirdBody->hide();
    ui->foruthBody->hide();
    ui->fifthBody->hide();
}

void Dialog::SuperFormRead()
{
    state=1;
    ui->magic->setEnabled(true);
    ui->magic->show();
    DepartFormRead();
}

void Dialog::on_magic_clicked()
{
    if(state==1)
    {
        HumanFormRead();
        state=0;
    }
    else
    {
        DepartFormRead();
        state=1;
    }
}

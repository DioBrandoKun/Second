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

QStringList Dialog::getData()
{
    if(!state)
    return {ui->firstBody->toPlainText(),
            ui->secondBody->toPlainText(),
            ui->thirdBody->toPlainText(),
            ui->foruthBody->toPlainText(),
            ui->fifthBody->toPlainText(),
    };
    else
        return {ui->firstBody->toPlainText()};
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

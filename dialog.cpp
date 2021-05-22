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



void Dialog::HumanForm(QStringList list)
{
    ui->first->setText("Имя");
    ui->second->setText("Фамилия");
    ui->third->setText("Отчество");
    ui->fourth->setText("Должность");
    ui->fifth->setText("Зарплата");

    ui->firstBody->setText(list[0]);
    ui->secondBody->setText(list[1]);
    ui->thirdBody->setText(list[2]);
    ui->foruthBody->setText(list[3]);
    ui->fifthBody->setText(list[4]);

}

void Dialog::DepartForm(QString name)
{
    ui->first->setText("Название");
    ui->firstBody->setText(name);

    ui->second->hide();
    ui->third->hide();
    ui->fourth->hide();
    ui->fifth->hide();

    ui->secondBody->hide();
    ui->thirdBody->hide();
    ui->foruthBody->hide();
    ui->fifthBody->hide();
}

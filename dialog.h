#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
#include <QRegExp>
namespace Ui {
class Dialog;
}

//Вспомогательная форма для отображения информации или заполнения
class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();

    //Возвращает заполненную или измененную информацию
    bool getData(QStringList& inp);

    //Вызывается для элемента с поведением ICenter
    //Позволяет менять тип формы с добавления человека
    //На добавление отдела
    void SuperFormRead();

    //Заполненная форма о человеке с его данными
    //@QStringList список данных для формы
    //1-Имя 2-Фамилия 3-Отчество 4-Должность 5-Зарплата
    void HumanForm(QStringList list);

    //Вызывается для добавления человека, форма с пустыми QTextEdit
    void HumanFormRead();

    //Заполненная форма о департаменте с его данными
    //@QStringList список данных для формы
    //1-Название
    void DepartForm(QString);

    //Вызывается для добавления департамента, форма с пустыми QTextEdit
    void DepartFormRead();
private slots:
    //Поведение для SuperFormRead(); меняет тип формы
    void on_magic_clicked();

private:
    //Текущее состояние формы 0-для департамента 1-для сотрудника
    bool state=0;
    Ui::Dialog *ui;
};

#endif // DIALOG_H

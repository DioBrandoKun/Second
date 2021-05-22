#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QAbstractButton>
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = nullptr);
    ~Dialog();
    QStringList getData();
    void SuperFormRead();
    void HumanForm(QStringList list);
    void HumanFormRead();
    void DepartForm(QString);
    void DepartFormRead();
private slots:
    void on_magic_clicked();

private:
    bool state=0;
    Ui::Dialog *ui;
};

#endif // DIALOG_H

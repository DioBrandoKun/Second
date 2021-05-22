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
    void HumanForm(QStringList list);
    void DepartForm(QString);
private:
    Ui::Dialog *ui;
};

#endif // DIALOG_H

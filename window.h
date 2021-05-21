#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "IComp.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE

class ProperItem: public QTreeWidgetItem
{
public:
    IComp* m_data=nullptr;
    void SetData(IComp* newData)
    {
        m_data=newData;
    }
};


class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

private:

    Ui::Window *ui;
};
#endif // WINDOW_H

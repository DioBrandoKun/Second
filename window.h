#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "IComp.h"

#include <QString>              //Парсинг XML
#include <QXmlStreamReader>
#include <QFile>
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

private slots:
    void on_pushButton_clicked();

private:
    IComp* data=nullptr;
    void Parse();
    Ui::Window *ui;
};
#endif // WINDOW_H

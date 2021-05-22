#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "IComp.h"

#include <QString>              //Парсинг XML
#include <QXmlStreamReader>
#include <QFile>

#include "dialog.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE




class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    Dialog* m_info=nullptr;
private slots:
    void on_pushButton_clicked();

    void on_remove_clicked();

    void on_tree_itemClicked(QTreeWidgetItem *item, int column);

    void on_tree_itemDoubleClicked(QTreeWidgetItem *item, int column);

    void ShowForm();

private:
    Departament* data=nullptr;
    void ShowTree();
    void Parse();
    Ui::Window *ui;
};
#endif // WINDOW_H

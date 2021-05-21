#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
    //m_tree=this->findChild<QTreeWidget*>("tree");
    //if(m_tree==nullptr)
    //    return;
    QTreeWidgetItem* item=new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("item: %1").arg(1)));//m_tree
    ui->tree->setColumnCount(1);

    ui->tree->insertTopLevelItem(0,item);


}

Window::~Window()
{
    delete ui;
}


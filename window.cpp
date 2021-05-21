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
#include <qDebug>
void Window::Parse()
{
    QFile file("tst.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        exit(0);
    }
    QXmlStreamReader root (&file);
    while (!root.atEnd() && !root.hasError())
    {
        QXmlStreamReader::TokenType token = root.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (root.name() == "department")
            {
                qDebug()<<root.name();
                QString dep_name = root.attributes().value("name").toString();
                continue;
            }
            if (root.name() == "employment")
            {
                qDebug()<<root.name();
                root.readNextStartElement();
                QString ser;
                QString name;
                QString mid_name;
                QString func;
                QString salar;
                if(root.name() == "surname")
                {
                    ser=root.readElementText();
                    root.readNextStartElement();
                }
                if (root.name() == "name")
                {
                     name=root.readElementText();
                     root.readNextStartElement();
                }
                if (root.name() == "middleName")
                {
                    mid_name=root.readElementText();
                    root.readNextStartElement();
                }
                if (root.name() == "function")
                {
                    func=root.readElementText();
                    root.readNextStartElement();
                }
                if (root.name() == "salary")
                {
                    salar=root.readElementText();
                    root.readNextStartElement();
                }
                qDebug()<<ser<<name<<mid_name<<func<<salar;
                continue;
            }

        }
    }
    qDebug()<<"End";
}

Window::~Window()
{
    delete ui;
}


void Window::on_pushButton_clicked()
{
    if(data!=nullptr)
        data->remove();
    ui->tree->clear();
    Parse();
}

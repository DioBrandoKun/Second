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
    QTreeWidgetItem* item=new QTreeWidgetItem(static_cast<QTreeWidget *>(nullptr), QStringList(QString("item: %1")));//m_tree
    ProperItem*      item2=(ProperItem*) item;
    //ui->tree->setColumnCount(1);

    //ui->tree->insertTopLevelItem(0,item2);

}
#include <qDebug>
void Window::Parse()
{
    QFile file("tst.xml");
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        exit(0);
    }
    QString name="Головной офис";
    data = new Departament(name,new ICenter());         //Создание основного офиса
    Departament*    dep=nullptr;
    Human*          hum=nullptr;

    QXmlStreamReader root (&file);
    while (!root.atEnd() && !root.hasError())
    {
        QXmlStreamReader::TokenType token = root.readNext();
        if (token == QXmlStreamReader::StartDocument)
            continue;
        if (token == QXmlStreamReader::StartElement)
        {
            if (root.name() == "department")            //Парсинг отдела
            {
                qDebug()<<root.name();
                QString dep_name = root.attributes().value("name").toString();
                qDebug()<<dep_name;
                if(dep!=nullptr)                        //Отдел добавляется в офис, только если начался парсинг нового отдела
                    data->add(dep);
                dep= new Departament(dep_name,new IDepart());
                continue;
            }
            if (root.name() == "employment")            //Парсинг человека
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
                hum = new Human(name,ser,mid_name,func,salar);
                if(dep!=nullptr)
                    dep->add(hum);
                qDebug()<<ser<<name<<mid_name<<func<<salar;
                continue;
            }

        }
    }
    if(dep!=nullptr)                //Под конец парсинга остается один офис
        data->add(dep);
    ShowTree();
    qDebug()<<"End";
}

Window::~Window()
{
    delete ui;
}
void Window::ShowTree()
{
    std::vector<std::pair<int,ProperItem*>> tree_vec;
    data->tree(tree_vec);
    ui->tree->setColumnCount(3);
    for(auto& pair:  tree_vec)
    {
        ui->tree->addTopLevelItem(pair.second);
    }
}

void Window::on_pushButton_clicked()
{
    if(data!=nullptr)
        data->remove();
    ui->tree->clear();
    Parse();
}

void Window::on_remove_clicked()
{
    auto* item=(ProperItem*)ui->tree->currentItem();
    item->m_data->remove();
    if(data->m_removed==true)
    {
        delete data;
        data=nullptr;
    }
    else
    {
        delete item;
    }
    ui->tree->clear();
    ui->m_text->clear();
    if(data!=nullptr)
        ShowTree();
}

void Window::ShowForm()
{
    this->show();
    this->setEnabled(true);
    delete m_info;
    m_info=nullptr;
}

void Window::on_tree_itemClicked(QTreeWidgetItem *item, int column)
{
    auto* selecItem=(ProperItem*)item;
    selecItem->m_data->m_show->show(selecItem->m_data,ui->m_text);
}

void Window::on_tree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    this->m_info = new Dialog();
    this->setEnabled(false);
    connect(this->m_info,SIGNAL(accepted()),this,SLOT(ShowForm()));

    this->hide();
    auto* selecItem=(ProperItem*)item;
    selecItem->m_data->m_show->showForm(selecItem->m_data,this->m_info);
}

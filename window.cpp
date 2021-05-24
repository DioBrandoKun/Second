#include "window.h"
#include "ui_window.h"

Window::Window(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Window)
{
    ui->setupUi(this);
}
#include <qDebug>
void Window::Parse()
{
    QString tmp = QFileDialog::getOpenFileName(0, "Choose file", "", "*.xml");
    if (tmp == 0) return;
    QFile file(tmp);
    if(!file.open(QFile::ReadOnly | QFile::Text)){
        return;
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
                QString dep_name = root.attributes().value("name").toString();
                if(dep!=nullptr)                        //Отдел добавляется в офис, только если начался парсинг нового отдела
                    data->add(dep);
                dep= new Departament(dep_name,new IDepart());
                continue;
            }
            if (root.name() == "employment")            //Парсинг человека
            {
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
                continue;
            }

        }
    }
    if(dep!=nullptr)                //Под конец парсинга остается один офис
        data->add(dep);
    ShowTree();
}

Window::~Window()
{
    delete ui;
}
void Window::ShowTree()
{
    ui->m_text->clear();
    ui->tree->clear();
    if(data==nullptr || data->m_removed) return;
    std::vector<std::pair<int,QTreeWidgetItem*>> tree_vec;
    m_pointer.clear();
    int count=1;
    data->tree(tree_vec,m_pointer,count);
    ui->tree->setColumnCount(count+1);      //Так как счет от 0
    for(auto& pair:  tree_vec)
    {
        ui->tree->addTopLevelItem(pair.second);
    }
}

void Window::on_pushButton_clicked()
{
    if(data!=nullptr)
    {
        data->remove();
        data=nullptr;
    }
    ui->tree->clear();
    MementoCollector::clearAhead();
    MementoCollector::claerBack();
    Parse();
}

void Window::on_remove_clicked()
{
    save_back();
    if(ui->tree->currentItem()==nullptr) return;
    auto* item=m_pointer[ui->tree->currentItem()];
    item->remove();
    if(data->m_removed==true)
    {
        data=nullptr;
    }
    ShowTree();

}

void Window::ShowForm()
{

    auto* selecItem=m_pointer[ui->tree->currentItem()];
    QStringList list_data;
    auto res=m_info->getData(list_data);
    m_info=nullptr;
    this->setEnabled(true);
    if(!res) return;
    save_back();
    selecItem->Chage(list_data);


    ShowTree();
}



void Window::ShowFormRejected()
{
    this->setEnabled(true);

    m_info=nullptr;
}


void Window::on_tree_itemClicked(QTreeWidgetItem *item, int column)
{
    auto* selecItem=m_pointer[item];
    selecItem->m_show->show(selecItem,ui->m_text);
}

void Window::on_tree_itemDoubleClicked(QTreeWidgetItem *item, int column)
{
    this->m_info = new Dialog();
    this->setEnabled(false);
    connect(this->m_info,SIGNAL(accepted()),this,SLOT(ShowForm()));
    connect(this->m_info,SIGNAL(rejected()),this,SLOT(ShowFormRejected()));

    auto* selecItem=m_pointer[item];
    selecItem->m_show->showForm(selecItem,this->m_info);
}

void Window::ShowFormAdd()
{

    auto* selecItem=m_pointer [ui->tree->currentItem()];
    QStringList list_out;
    auto res=m_info->getData(list_out);
    if(!res) return;
    this->setEnabled(true);
    m_info=nullptr;
    save_back();
    selecItem->Add(list_out);



    ShowTree();
}

void Window::ShowFormCreate()
{

    QStringList list_data;
    auto res=m_info->getData(list_data);
    this->setEnabled(true);
    m_info=nullptr;
    if(!res)
    {
        return;
    }
    save_back();
    this->data =new Departament(list_data[0],new ICenter());
    ShowTree();
}
//Add действие
void Window::on_pushButton_3_clicked()
{
    if(ui->tree->currentItem()==nullptr &&  data!=nullptr) return;

    this->m_info = new Dialog();
    this->setEnabled(false);
    if(data==nullptr)
    {
        connect(this->m_info,SIGNAL(accepted()),this,SLOT(ShowFormCreate()));
        connect(this->m_info,SIGNAL(rejected()),this,SLOT(ShowFormRejected()));
        m_info->show();
        m_info->DepartFormRead();
        return;
    }
    connect(this->m_info,SIGNAL(accepted()),this,SLOT(ShowFormAdd()));

    connect(this->m_info,SIGNAL(rejected()),this,SLOT(ShowFormRejected()));

    auto* selecItem=m_pointer [ui->tree->currentItem()];
    selecItem->showReadForm(this->m_info);
}



IMemento* Window::save()
{
    if(data==nullptr) return new Memento(nullptr,this);;
    Departament* memory=new Departament(data->m_name,new ICenter());
    data->clone(memory,true);
    Memento* out =new Memento(memory,this);
    return out;
}

void Window::save_back()
{
    MementoCollector::clearAhead();                 //Каждый раз когда мы делаем новое действие, мы создаем новую цепочку Ahead
    ui->ahead->setEnabled(false);
    MementoCollector::addBack(save());
    if(MementoCollector::getBackSize()>0) ui->back->setEnabled(true);
}

void Window::on_back_clicked()
{
    MementoCollector::addAhead(save());
    MementoCollector::restoreBack();
    if(MementoCollector::getBackSize()==0) ui->back->setEnabled(false);
    if(MementoCollector::getAheadSize()>0) ui->ahead->setEnabled(true);
}

void Window::on_ahead_clicked()
{
    MementoCollector::addBack(save());
    MementoCollector::restoreAhead();
    if(MementoCollector::getBackSize()>0) ui->back->setEnabled(true);
    if(MementoCollector::getAheadSize()==0) ui->ahead->setEnabled(false);
}

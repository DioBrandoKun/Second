#ifndef WINDOW_H
#define WINDOW_H

#include <QMainWindow>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include "IComp.h"

#include <QString>              //Парсинг XML
#include <QXmlStreamReader>
#include <QFile>

#include <QMap>
#include "dialog.h"
#include "memento.h"
QT_BEGIN_NAMESPACE
namespace Ui { class Window; }
QT_END_NAMESPACE



//Основное окно приложения
class Window : public QMainWindow
{
    Q_OBJECT

public:
    Window(QWidget *parent = nullptr);
    ~Window();

    Dialog* m_info=nullptr;



private slots:
    //Вызов парсера, очищение существующих данных
    void on_pushButton_clicked();
    //Удаление выбранного элемента, отображение нового дерева
    void on_remove_clicked();
    //Вывод информации в вспомогательном окне
    void on_tree_itemClicked(QTreeWidgetItem *item, int column);
    //Вывод информации о элемента, форма становится недоступной
    void on_tree_itemDoubleClicked(QTreeWidgetItem *item, int column);
    //В данные были внесены изменения, отображение нового дерева
    void ShowForm();
    //Данные не были затронуты, форма снова доступна
    void ShowFormRejected();
    //Была введена информация для нового элемента
    void ShowFormAdd();
    //Нажатие на кнопку добавить, вывод диалогового окна
    void on_pushButton_3_clicked();

    void on_back_clicked();

    void on_ahead_clicked();

private:
    //Класс воспоминаний, нужен для восстановления данных
    class Memento:public IMemento
    {
        Window*    object;
        Departament* data;
     public:
        Memento(Departament* info,Window* obj):data(info),object(obj){};
        void restoreData() override
        {
            object->data->remove();
            object->data=nullptr;
            object->data=new Departament(data->m_name,new ICenter());
            data->clone(object->data,true);
            object->ShowTree();
        }
    };
    friend Memento;

    //Действие которое можно отменить
    void save_back();

    //Сохранение текущего состояния
    IMemento* save();

    //Массив хранящий для каждого элемента дерева, его ссылку на данные
    //При попытке расширить класс QTreeWidgetItem появились проблемы
    QMap<QTreeWidgetItem*,IComp*> m_pointer;

    //Данные компановщика
    Departament* data=nullptr;

    //Отображение дерева
    void ShowTree();

    //Вызов парсера
    void Parse();
    Ui::Window *ui;
};
#endif // WINDOW_H

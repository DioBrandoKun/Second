#ifndef PROPERITEM_H
#define PROPERITEM_H
#include <QTreeWidgetItem>
#include "IComp.h"
class ProperItem: public QTreeWidgetItem
{
public:
    IComp* m_data=nullptr;
    void SetData(IComp* newData)
    {
        m_data=newData;
    }
};
#endif // PROPERITEM_H

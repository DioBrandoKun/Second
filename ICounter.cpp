#include "IComp.h"

void InfoView::Count(Human* obj)
{
    m_num++;
    all_salary+=obj->m_salary;
}
void InfoView::Count(Departament* obj)
{
    m_dep++;
}

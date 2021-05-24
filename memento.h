#ifndef MEMENTO_H
#define MEMENTO_H
#include "IComp.h"

class IMemento
{
public:
   virtual void restoreData()=0;
    virtual ~IMemento(){};
};

class MementoCollector
{
private:
   static std::vector<IMemento*> m_back;
   static std::vector<IMemento*> m_ahead;
   MementoCollector(){};
public:
   static void addBack(IMemento* newMem)
   {
        m_back.push_back(newMem);
   }
   static void addAhead(IMemento* newMem)
   {
        m_ahead.push_back(newMem);
   }
   static void restoreBack()
   {
        IMemento* mem=m_back.back();
        mem->restoreData();
        m_back.pop_back();
   }
   static void restoreAhead()
   {
        IMemento* mem=m_ahead.back();
        mem->restoreData();
        m_ahead.pop_back();
   }
   static unsigned getBackSize()
   {
       return m_back.size();
   }

   static unsigned getAheadSize()
   {
       return m_ahead.size();
   }

   static void claerBack()
   {
    for(size_t i=0;i< m_back.size();i++)
        delete m_back[i];
    m_back.erase(m_back.begin(),m_back.end());
   }
   static void clearAhead()
   {
    for(size_t i=0;i< m_ahead.size();i++)
        delete m_ahead[i];
    m_ahead.erase(m_ahead.begin(),m_ahead.end());
   }
};
#endif // MEMENTO_H

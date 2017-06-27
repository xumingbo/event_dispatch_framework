
#include "EventDispatcher.h"

template <typename T_EVENT>
class EventSource : public EventSrcProxy
{
typedef typename std::vector<T_EVENT*>::iterator iterator;
public:
    EventSource() {};
    virtual ~EventSource(){};
    void pollEvent() 
    {
       //std::vector<T_EVENT *>::iterator it_Event;
       iterator it_Event;
        it_Event = m_ActiveEventPool.begin();
        while (it_Event != m_ActiveEventPool.end())
       {   EventProxy *ei = 
        static_cast<EventProxy*>(*it_Event);
            if (ei->eventTrigged()) //an event fired
            {   theDispatcher().addEventToDispachQueue(ei);
                //remove this event from active pool
                ei->deactivateEvent();
                m_ActiveEventPool.erase(it_Event);
            }
            else
                it_Event++;
        }
    }
    void addEvent(T_EVENT * const ei)
    {   m_ActiveEventPool.push_back(ei);} //add to event pool
    const int getEventCount() const {return m_ActiveEventPool.size();}
protected:
    std::vector<T_EVENT * >   m_ActiveEventPool;
};

template <typename T_SRC>
class Event : public EventProxy
{
//protected:  
public:  
    static T_SRC theEventSource; 
    virtual ~Event () {}
};

//definition of static member of Event<T_SRC>, 
//It is specialized with class Event<T_SRC>
template <typename T_SRC>
T_SRC Event<T_SRC>::theEventSource;


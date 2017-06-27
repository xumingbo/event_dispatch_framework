#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include <iostream>
#include <vector>
#include <queue>
#include <time.h>

//forward declarations
class EventSrcProxy;

class EventProxy {
public:
    EventProxy ():m_restore(false) {};
    virtual bool eventTrigged() = 0;
    virtual bool activateEvent() = 0;
    virtual void deactivateEvent() = 0;
    virtual void eventProcess() = 0;
    const bool operator<(const EventProxy & rhs) const 
        {return getTimeStamp() < rhs.getTimeStamp();}
    const time_t getTimeStamp() const {return m_timeStamp;}
protected:
    void setRestore(bool b) {m_restore = b;}
    const bool IsRestore() const {return m_restore;}

    //dtor in "protected", so an object of a derived class 
    //can only be created with "new" operator.
    virtual ~EventProxy () {};
private:
    time_t m_timeStamp;
    bool    m_restore;
};

struct EarlierEvent
{   bool operator ()(const EventProxy * left, const EventProxy * right)
    {return *left < *right;}
};

typedef std::vector<EventSrcProxy * > EvetnSourceVector;
typedef std::vector<EventProxy * > EventVector;
typedef std::priority_queue<EventProxy*,EventVector,EarlierEvent> EventQueue;
class EventDispatcher
{
public:
    void eventSourceRegister(EventSrcProxy * const es)
      {m_eventSources.push_back(es);}
    void addEventToDispachQueue(EventProxy * const ei)
      {m_eventDispatchQueue.push( ei);}
    void Loop();
    void terminate() { m_loop = false;}
friend EventDispatcher & theDispatcher();   
private:
    EventDispatcher(): m_loop(true) {};
        EvetnSourceVector  m_eventSources;
    EventQueue   m_eventDispatchQueue;
    bool m_loop;
};

//forward declarations
EventDispatcher & theDispatcher();

class EventSrcProxy
{
public:
    EventSrcProxy(){theDispatcher().eventSourceRegister(this);}
    virtual ~EventSrcProxy(){};
    virtual void pollEvent() = 0;
};

#endif


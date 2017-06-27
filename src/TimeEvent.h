
#include "EventDispatcher.h"
#include "EventSource.h"

class TimeEvent;  //forward declaration.
class TimeEventSource : public EventSource <TimeEvent>
{
public:
    TimeEventSource() {};
    ~TimeEventSource() {};
};
//call back declaration with specific signature.
typedef void (*timerCallback)(time_t timer);

class TimeEvent : public Event <TimeEventSource>
{
public:
    explicit TimeEvent(unsigned int timer, timerCallback cb = NULL, bool
periodic = false):m_timer(timer), m_callBack(cb)
        {   setRestore(periodic);
        activateEvent();
        }
    void    eventProcess(); // impl of virtual,
    bool    eventTrigged();
    bool    activateEvent();
    void    deactivateEvent() {};

    time_t  getTimer() const { return m_timer;}
    time_t  getExpireTime() const { return m_expireTime;}
    void        setExpireTime(time_t t) {m_expireTime = t;}
    ~TimeEvent () {}
private:
    unsigned int m_timer;
    time_t m_expireTime;
    timerCallback m_callBack;
};

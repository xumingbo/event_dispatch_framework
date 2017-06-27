
#include "TimeEvent.h"

bool TimeEvent::activateEvent()
{   time_t current_time = time(NULL);
    setExpireTime(current_time + getTimer());
    // TODO setTimeStamp(getExpireTime());//for position in dispatch queue
    Event<TimeEventSource>::theEventSource.addEvent(this);//put it on polling queue
    //this syntax also fine:
    //theEventSource.addEvent(this);//put it on polling queue
    return true;
}
void TimeEvent::eventProcess()
{   if (m_callBack != NULL) (*m_callBack)(m_timer);
    if (IsRestore())    
        activateEvent();  //re-activated
    else
        delete this; //all objects of this class are created with 
                 //"new" operator, so self delete is valid.
}
bool TimeEvent::eventTrigged()
{   time_t current_time = time(NULL);
    time_t time_remaind = getExpireTime() - current_time;
    if (time_remaind <= 0)
        return true;
    else
        return false;
}
 

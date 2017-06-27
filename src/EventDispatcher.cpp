
#include "EventDispatcher.h"

void EventDispatcher::Loop()
{   
    while (m_loop)
    {   //For each event source, poll event
        EvetnSourceVector::iterator it_eSrc;
        for (it_eSrc = m_eventSources.begin(); it_eSrc != m_eventSources.end(); it_eSrc ++)
        {   
            (*it_eSrc)->pollEvent();
        }
        //process events in dispatch queue
        while (!m_eventDispatchQueue.empty())
        {   EventProxy *eip;
            eip = m_eventDispatchQueue.top();
            m_eventDispatchQueue.pop();
            eip->eventProcess();
        }
    }
}

EventDispatcher & theDispatcher()
{
static EventDispatcher _disp;
    return _disp;
}


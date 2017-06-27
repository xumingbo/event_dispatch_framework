
#include "TimeEvent.h"

void te_Callback1(time_t t)
{   
    std::cout << "every " << t << " seconds, dancing.\n";
}

void te_Callback2(time_t t)
{   
    std::cout << " terminating main loop.\n";
    theDispatcher().terminate();
}

int main(void)
{   TimeEvent *timeRepeat = new TimeEvent (5, te_Callback1, true);
    TimeEvent *timeTerm = new TimeEvent (20, te_Callback2);
    theDispatcher().Loop();
    delete timeRepeat;
    timeTerm = NULL; //timeTerm self destructed
    return 0;
}



#include "TimeEvent.h"

void te_Callback1(time_t t)
{   
    std::cout << "every " << t << " second, dancing.\n";
}

void te_Callback2(time_t t)
{   
    std::cout << " terminating main loop.\n";
    theDispatcher().terminate();
}

int main(void)
{   TimeEvent *timeRepeat = new TimeEvent (1, te_Callback1, true);
    TimeEvent *timeTerm = new TimeEvent (6, te_Callback2);
    theDispatcher().Loop();
    delete timeRepeat;
    timeTerm = NULL; //timeTerm self destructed
    return 0;
}


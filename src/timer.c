#include <sys.h>
#include <timer.h>

void init_timer0(const timer_type timertype, timer_mode timermode)
{
    if (timertype == TIMER)
    {

    } 
    else 
    {

    }
}

void init_timer(const timer_id timerid, const timer_type timertype, timer_mode timermode)
{ 
    if (timerid == TIMER0)
    {
        init_timer0(timertype, timermode);
    } 
    else if (timerid == TIMER1) 
    {

    }
}
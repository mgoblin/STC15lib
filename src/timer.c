#include <sys.h>
#include <bits.h>
#include <timer.h>

//TODO implements interrupt version 
//TODO implements mode1-3

void timer_mode0_init(const timer_id timerid)
{ 
    if (timerid == TIMER0) 
    {
        set_bits(TMOD, 0x08, 0);
    } 
    else if (timerid == TIMER1)
    {
        set_bits(TMOD, 0x08, 4);
    }
}

void timer_mode0_run_and_wait(const timer_id timerid, uint8_t tl_value, uint8_t th_value)
{
    if (timerid == TIMER0)
    {
        TL0 = tl_value;
        TH0 = th_value;

        TF0 = 0;
        TR0 = 1;

        while(!TF0)
        {
        }
    }
    else if (timerid == TIMER1)
    {
        TL1 = tl_value;
        TH1 = th_value;

        TF1 = 0;
        TR1 = 1;

        while(!TF1)
        {
        }
    }
}
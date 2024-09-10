#include <sys.h>
#include <timer.h>

//TODO implements interrupt version 

void timer0_mode0_init()
{ 
    EA = 1; // set global interrupts enabled flag
    TMOD = 0x08;
}

void timer0_mode0_run_once_and_wait(uint8_t tl_value, uint8_t th_value)
{
    TL0 = tl_value;
    TH0 = th_value;

    TF0 = 0;
    TR0 = 1;

    while(!TF0)
    {
    }

    TF1 = 0;
}

void timer0_mode0_start(uint8_t th_value, uint8_t tl_value)
{
    TL0 = tl_value;
    TH0 = th_value;

    ET0 = 1; // set timer0 interrupt enabled flag

    TF0 = 0;
    TR0 = 1;
}

void timer0_mode0_stop()
{
    ET0 = 0;
    TF0 = 0;
    TR0 = 0;
}
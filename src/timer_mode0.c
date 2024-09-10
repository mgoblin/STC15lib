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

// void timer_mode0_start( const timer_id timerid, 
//                         uint8_t th_value, uint8_t tl_value)
// {
//     if (timerid == TIMER0)
//     {
//         TL0 = tl_value;
//         TH0 = th_value;

//         ET0 = 1; // set timer0 interrupt enabled flag

//         TF0 = 0;
//         TR0 = 1;

//     }
//     else if (timerid == TIMER1)
//     {
//         TL1 = tl_value;
//         TH1 = th_value;

//         ET1 = 1; // set timer1 interrupt enabled flag

//         TF1 = 0;
//         TR1 = 1;
//     }
// }

// void timer_mode0_stop(const timer_id timerid)
// {
    
//     if (timerid == TIMER0)
//     {
//         ET0 = 0;
//         TF0 = 0;
//         TR0 = 0;
//     }
//     else if (timerid == TIMER1)
//     {
//         ET1 = 0;
//         TF1 = 0;
//         TR1 = 0;
//     }
// }

// void timer0ISR(void) __interrupt(1)
// {
//     P10 = !P10;
// }
/**
 * How to output meander to P3.0. Meander frequency is controlled by timer2.
 */
#include <timer2_mode0.h>

#define LED P10

void timer2ISR(void) __interrupt(12)
{
    LED = !LED;
}

void main()
{
    timer2_mode0_12T_init(); // init timer2
    // enable output of timer to P3.0 pin. The signal is _|‾|_|‾|_
    timer2_mode0_enable_P30_output(true); 

    timer2_mode0_start(0xffff); //start timer

    while (1) {}
}
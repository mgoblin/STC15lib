#include <sys.h>
#include <delay.h>
#include <timer.h>

#include <uart.h>
#include <stdio.h>
#include <delay.h>

#define LED P10

void timer2ISR(void) __interrupt(12)
{
    LED = !LED;
}

void main()
{
    timer2_mode0_12T_init(); // reinit timer2
    // enable output of timer to P3.0 pin. The signal is _|‾|_|‾|_
    timer2_mode0_enableP30_output(true); 

    timer2_mode0_start(0xffff); //start timer

    while (1) {}
}
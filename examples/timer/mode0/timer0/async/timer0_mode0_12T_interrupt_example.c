/**
 * How to start timer0.
 * 
 * Timer0 started with interrupt handler. Interrupt hanlder doing LED blinking.
 * After start timer main program going to endless waiting, but timer will ticks.
 */
#include <timer0_mode0.h>

#define LED P10

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    timer0_mode0_12T_init();

    timer0_mode0_start(0xffff);

    while(1){};
}
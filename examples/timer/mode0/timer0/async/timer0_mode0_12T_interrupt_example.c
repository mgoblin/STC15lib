/**
 * How to start timer0
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
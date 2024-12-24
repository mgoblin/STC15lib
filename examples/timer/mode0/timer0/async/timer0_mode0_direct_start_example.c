/**
 * How to run timer0 with direct TL0 and TH0 values.
 * 
 * Timer start with max ticks value corresponding TL0 = TH0 = 0 and 
 * LED is blinking
 */
#include <timer0_mode0.h>

#define LED P10

void timerISR() __interrupt 1
{
    LED = !LED;
}

void main()
{
    timer0_mode0_12T_init();
    timer0_mode0_direct_start(0x00, 0x00);

    while (1) {}
    
}
/** 
 * How to direct start timer0
 * 
 * Load timer ticks directly to MCU regisrers and start 
 * timer with interrupt handler.
 * Interrupt handler do LED blinking.
 */
#include <timer0_mode3.h>
#include <frequency.h>

#define LED P10


void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    set_frequency_divider_scale(2);

    timer0_mode3_12T_init();
    timer0_mode3_direct_start(0x00, 0x00);

    while (1) {}
}
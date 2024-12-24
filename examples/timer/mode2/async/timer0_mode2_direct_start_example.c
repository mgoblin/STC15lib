/**
 * How to start timer0 in mode2 with direct set of timer value
 */

#include <timer0_mode2.h>
#include <frequency.h>

#define LED P10

#define BLINKS 10
uint8_t interrupt_count = 0;

void timerISR() __interrupt(1)
{
    if (interrupt_count >= BLINKS)
    {
        interrupt_count = 0;
        LED = !LED;
    }
    else 
    {
        interrupt_count++;
    }
}

void main()
{
    set_frequency_divider_scale(7);

    timer0_mode2_12T_init();
    timer0_mode2_direct_start(0x00);

    while (1){}
}
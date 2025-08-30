/**
 * How to delay with timer0 in mode2 (low level code)
 */
#include <timer0_mode2.h>

#define LED P10

void timerISR() __interrupt(1)
{
}

void main()
{
    TMOD |= 2; // timer0_mode2_12T_init() should be used

    while(1)
    {
        for(uint16_t i = 0; i < 1000; i++)
        {
            timer0_mode2_delay(0xff);
        }
        LED = !LED;
    }
}
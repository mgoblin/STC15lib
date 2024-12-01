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
    TMOD |= 2;

    while(1)
    {
        for(uint16_t i = 0; i < 1000; i++)
        {
            TL0 = 0; //0xff ticks
            TF0 = 0;
            TR0 = 1;
            while(!TF0) {}

            //timer0_mode2_delay(0xff);
        }
        LED = !LED;
    }
}
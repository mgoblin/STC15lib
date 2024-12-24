/**
 * How to start timer0 in mode1 with direct set TH0 and TL0 registers.
 */
#include <timer0_mode1.h>

#define LED P10
#define TH0_VALUE 0x00
#define TL0_VALUE 0x00

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    timer0_mode1_12T_init();

    while (1) 
    {
        while (is_timer0_mode1_started()) {}
        timer0_mode1_direct_start(TH0_VALUE, TL0_VALUE);
    }
    
}
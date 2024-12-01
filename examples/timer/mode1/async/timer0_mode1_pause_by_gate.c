/**
 * How to pause/resume timer0 using gate in mode1
 */
#include <timer0_mode1.h>
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

#define INT0 P32

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    timer0_mode1_12T_init();
    timer0_mode1_start(0xffff); 

    INT0 = 0;

    while (1)
    {
            timer0_mode1_open_gate();
            delay_ms(2000);
            
            timer0_mode1_close_gate();
            LED = OFF;
            delay_ms(2000);
    }
}
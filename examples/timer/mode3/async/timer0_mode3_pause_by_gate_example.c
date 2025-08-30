/**
 * How to pause/resume timer0 in mode3
 * 
 * LED blinking starts and stop using open/close the timer0 gate 
 */
#include <timer0_mode3.h>
#include <delay.h>

#define LED P10

#define INT0 P32

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    timer0_mode3_12T_init();
    timer0_mode3_start(0xffff); 
    INT0 = 0;

    while (1)
    {
            timer0_mode3_open_gate();
            delay_ms(2000);
            
            timer0_mode3_close_gate();
            LED = 1; // LED off
            delay_ms(2000);
    }
}
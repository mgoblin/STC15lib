/**
 * How to pause/resume timer0 in mode0 using gate
 * 
 * LED blinking during 2 seconds and than stop on 2 seconds.
 */
#include <timer0_mode0.h>
#include <delay.h>

#define LED P10
#define ON 0
#define OFF 1

#define INT0 P32

void timerISR() __interrupt(INTERRUPT_TIMER0)
{
    LED = !LED;
}

void delay_ms_f(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
    timer0_mode0_12T_init();
    enable_timer0_interrupt();
    timer0_mode0_start(0xffff); 
    
    INT0 = 0; // Set INT0 to LOW. Timer paused/resumed by gate

    while (1)
    {
            timer0_mode0_open_gate(); // timer is resumed and LED is blinking 
            delay_ms_f(2000);
            
            timer0_mode0_close_gate(); // timer is paused and LED is not blinking 
            LED = OFF;
            delay_ms_f(2000);
    }
}
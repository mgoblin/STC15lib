/**
 * How to start and stop timer0
 */

#include <delay.h>
#include <timer0_mode0.h>

#define LED P10
#define OFF 1
#define ON 0

uint8_t interrupt_counter = 0; // interrupt counter. 

void timer0ISR(void) __interrupt(1)
{
    // Every 12th interrupt call switch LED state and reset counter
    if (interrupt_counter++ == 12)
    {
        interrupt_counter = 0;
        LED = !LED;
    }
}

void delay_ms_f(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
    timer0_mode0_1T_init();

    while(1)
    {
        // LED blinking during 1 second 
        timer0_mode0_start(0xffff);
        delay_ms_f(1000);
        LED = OFF;

        // LED not blinking during 2 seconds
        timer0_mode0_stop();
        interrupt_counter = 0;
        delay_ms_f(2000);
    }
}
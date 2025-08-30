/** 
 * How to start and stop timer0 in mode3.
 * 
 * LED blinking 1 second after timer started and then 2 seconds not blinking.
 */
#include <delay.h>
#include <timer0_mode3.h>

#define LED P10

void timer0ISR(void) __interrupt(1) __using(1)
{
    LED = !LED;
}

void delay(uint16_t ms)
{
    delay_ms(ms);
}

void main()
{
    set_frequency_divider_scale(4);

    timer0_mode3_1T_init();

    // LED blinking during 1 second 
    timer0_mode3_start(0xffff);
    delay(1000);
    LED = 1; // LED off

    // LED not blinking during 2 seconds
    timer0_mode3_stop();
    delay(2000);
}
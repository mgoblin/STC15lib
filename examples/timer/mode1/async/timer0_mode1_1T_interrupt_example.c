/**
 * How to handle timer0 interrupt in mode1.
 * 
 * Interrupt handler toggle LED pin state and LED is blinking.
 * Main program start timer0 in mode1
 * 
 * LED blinking during timer0 is started (1 second) and than not blinking 
 * until timer0 is stopped (2 sec).
 */
#include <timer0_mode1.h>

#include <delay.h>
#include <frequency.h>

#define LED P10

void timer0ISR(void) __interrupt(1)
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

    timer0_mode1_1T_init();

    while (1)
    {
        // LED blinking during 1 second 
        timer0_mode1_start(0xffff);
        delay(1000);
        LED = 1; // LED off

        // LED not blinking during 2 seconds
        timer0_mode1_stop();
        delay(2000);
    }
}
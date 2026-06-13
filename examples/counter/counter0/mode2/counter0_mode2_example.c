/**
 * How to use counter0 in mode2.
 * 
 * Pin T0 used as an input for counter0. 
 * 
 * After init T0 programmatically changed 
 * and current counter0 value is printed to UART.
 * 
 * After counter overflow LED is change it state.  
 */
#include <counter0_mode2.h>
#include <gpio.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

#define LED P10

#define INITIAL_COUNTER_VALUE 0x00

void timer0ISR(void) __interrupt(INTERRUPT_COUNTER0)
{
    LED = !LED;
}

void main()
{
    uart1_init(9600);

    counter0_mode2_init();
    counter0_mode2_start(INITIAL_COUNTER_VALUE);
    
    pin_quasi_bidiretional_init(P3, 4);

    while (1) {
        // Change pin state. Counter should increments
        P34 = !P34;
        if (!T0) // react on low value T0 pin only
        {
            printf_tiny("Counter value: %u\r\n", 
                counter0_mode2_get_value()
            );
        }
    }
}
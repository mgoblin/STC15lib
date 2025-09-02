/**
 * How to use counter0 in mode0.
 * 
 * This example configures counter0 to count from COUNTER_INIT_VALUE
 * to 65535 (100 counts).
 * Pin T0 used as an input for counter0. 
 * 
 * After init T0 programmatically changed 
 * and current counter0 value is printed to UART.
 * 
 * After counter overflow LED is change it state.  
 */
#include <counter0_mode0.h>
#include <pin.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

#define LED P10
#define COUNTER_INIT_VALUE 65435U // Initial counter value

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    uart1_init(9600);

    counter0_mode0_init();
    counter0_mode0_start(COUNTER_INIT_VALUE);
    
    pin_quasi_bidiretional_init(P3, 4);

    while (1) {
        T0 = !T0;
        delay_ms(50);
        if (!T0) // react on T0 pin change to low value only
        {
            printf_tiny(
                "Tick %u\r\n", 
                counter0_mode0_get_value() - COUNTER_INIT_VALUE);
        }
    }
}
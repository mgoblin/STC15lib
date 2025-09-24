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
#include <pin.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

#define LED P10

void timer0ISR(void) __interrupt(1)
{
    LED = !LED;
}

void main()
{
    uart1_init(9600);

    counter0_mode2_init();
    counter0_mode2_start(0xFF);
    
    pin_quasi_bidiretional_init(P3, 4);

    while (1) {
        T0 = !T0;
        delay_ms(5);
        if (!T0) // react on T0 pin change to low value only
        {
            printf_tiny(
                "Tick %u\r\n", 
                0 //counter0_mode0_get_value()
            );
        }
    }
}
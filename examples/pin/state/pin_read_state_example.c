/**
 * How to read pin state (LOW or HIGH)
 */
#include <pin.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define PIN P10

void main()
{
    pin_input_only_init(P1, 0);

    uart1_init(9600);
    while (1)
    {
        printf_tiny("PIN is %s\n", PIN == 1 ? "HIGH" : "LOW");
        delay_ms(500);
    }
    
}
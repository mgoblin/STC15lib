/**
 * How to read pin value (LOW or HIGH)
 * 
 * STC15_Button.jpg circuit should be implemented.
 * The button change P10 value between HIGH (button is not pressed) 
 * and LOW (when button is pressed) 
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
        printf_tiny("PIN is %s\r\n", PIN == 1 ? "HIGH" : "LOW");
        delay_ms(500);
    }
    
}
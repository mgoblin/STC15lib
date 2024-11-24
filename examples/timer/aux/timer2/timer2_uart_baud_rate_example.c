/**
 * How to use timer2 as baudrate generator for UART1
 */

#include <uart.h>
#include <stdio.h>

#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <delay.h>

#define UART_BAUDRATE 74880

void main()
{
    // UART1 on init use timer2_mode0_baudrate_to_ticks. 
    uart1_init(UART_BAUDRATE);
    
    while (1)
    {
        printf_tiny("Calulated timer2 ticks value is 0x%x\n", timer2_mode0_baudrate_to_ticks(UART_BAUDRATE));
        delay_ms(500);
    }
    
}
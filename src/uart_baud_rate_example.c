#include <uart.h>
#include <stdio.h>

#include <delay.h>

void main()
{
    const uint16_t uart_baudrate = 9600;
    uart1_init(uart_baudrate);

    uint8_t T2L_value = (65536 - (MAIN_Fosc/4/uart_baudrate)); //Set the preload value
    uint8_t T2H_value = (65536 - (MAIN_Fosc/4/uart_baudrate))>>8;


    while (1)
    {
        printf_tiny("T2L and T2H values is 0x%x%x\n", T2H_value, T2L_value);
        delay_ms(500);
    }
    
}
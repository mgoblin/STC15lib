#include <uart.h>
#include <stdio.h>

#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <delay.h>

#define UART_BAUDRATE 9600UL

void main()
{
    
    set_frequency_divider_scale(2);

    uart1_init(UART_BAUDRATE);

    uint16_t ticks = timer2_mode0_baudrate_to_ticks(UART_BAUDRATE);

    while (1)
    {
        printf_tiny("Timer2 ticks value is %u\n", ticks);
        delay_ms(500);
    }
    
}
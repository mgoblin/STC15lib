#include <uart.h>
#include <stdio.h>

#include <timer2_mode0.h>
#include <timer2_to_ms.h>

#include <delay.h>

#define UART_BAUDRATE 9600

void main()
{
    
    set_frequency_divider_scale(2);

    uint16_t ticks = uart1_init(UART_BAUDRATE);

    while (1)
    {
        printf_tiny("Timer2 ticks value is 0x%x\n", ticks);
        delay_ms(500);
    }
    
}
/**
 * Demonstrate how to enable timer2 as UART1 baud rate generator
 * 
 */
#include <timer2_mode0.h>

#include <delay.h>

#define LED P10

void main()
{
    timer2_mode0_12T_init();

    while (1)
    {
        enable_timer2_mode0_as_uart1_baud_rate(!LED);
        LED = is_timer2_mode0_as_uart1_baud_rate_enabled();
        delay_ms(1000);
    }
}
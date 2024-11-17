#include <sys.h>
#include <timer_common.h>
#include <timer0_mode0.h>
#include <timer0_mode1.h>
#include <delay.h>
#include <uart.h>

#include <stdio.h>

#define LED P10

void main()
{
    uart_init(9600);

    while (1)
    {
        printf_tiny("========================\n");

        timer0_mode0_12T_init();
        uint8_t mode = get_timer0_mode();
        timer_clock_divider_t divider =  get_timer0_clock_divider();
        printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);

        timer0_mode0_1T_init();
        mode = get_timer0_mode();
        divider =  get_timer0_clock_divider();
        printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);
        
        timer0_mode1_12T_init();
        mode = get_timer0_mode();
        divider =  get_timer0_clock_divider();
        printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);
        
        printf_tiny("========================\n");

        delay_ms(5000);

    }
}
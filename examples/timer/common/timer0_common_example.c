#include <sys.h>
#include <timer_all.h>
#include <delay.h>
#include <uart.h>

#include <stdio.h>

#define LED P10

void main()
{
    uart_init(9600);

    while (1)
    {
        timer0_mode0_12T_init();
        uint8_t mode = get_timer0_mode();
        timer_clock_divider_t divider =  get_timer0_clock_divider();
        printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);

        delay_ms(500);

        timer0_mode0_1T_init();
        mode = get_timer0_mode();
        divider =  get_timer0_clock_divider();
        printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);
        
        delay_ms(500);

        timer0_mode1_12T_init();
        mode = get_timer0_mode();
        divider =  get_timer0_clock_divider();
        printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);

        delay_ms(500);

        LED = !LED;
        
    }
}
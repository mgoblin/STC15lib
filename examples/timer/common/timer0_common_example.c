/**
 * How to get timer0 mode and divider
 * 
 */
#include <timer_common.h>
#include <timer0_mode0.h>
#include <timer0_mode1.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

#define LED P10

void print_timer0_mode_and_divider()
{
    uint8_t mode = get_timer0_mode();
    timer_clock_divider_t divider =  get_timer0_clock_divider();
    printf_tiny("Timer mode is %d and divider is %d\r\n", mode, divider);
}

void main()
{
    uart1_init(9600);

    while (1)
    {
        printf_tiny("========================\r\n");

        timer0_mode0_12T_init();
        print_timer0_mode_and_divider();

        timer0_mode0_1T_init();
        print_timer0_mode_and_divider();
        
        timer0_mode1_12T_init();
        print_timer0_mode_and_divider();
        
        printf_tiny("========================\r\n");

        delay_ms(1000);
    }
}

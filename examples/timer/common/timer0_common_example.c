/**
 * How to get timer0 mode, divider and ticks count
 * 
 */
#include <timer_common.h>
#include <timer0_mode0.h>
#include <timer0_mode1.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

void print_timer0_configs()
{
    uint8_t mode = get_timer0_mode();
    timer_clock_divider_t divider =  get_timer0_clock_divider();
    uint16_t ticks_count = 0;
    printf_tiny(
        "Timer mode is %u, divider is %u and ticks count is %u\r\n", 
        mode, 
        divider,
        ticks_count
    );
}

void main()
{
    uart1_init(9600);

    while (1)
    {
        printf_tiny("========================\r\n");

        timer0_mode0_12T_init();
        timer0_mode0_start(10000);
        print_timer0_configs();

        timer0_mode0_1T_init();
        timer0_mode0_start(1500);
        print_timer0_configs();
        
        timer0_mode1_12T_init();
        timer0_mode0_start(3500);
        print_timer0_configs();
        
        printf_tiny("========================\r\n");

        delay_ms(1000);
    }
}

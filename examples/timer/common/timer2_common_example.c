/**
 * How to get timer2 mode and divider
 */
#include <timer_common.h>
#include <timer2_mode0.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

void print_timer2_configs()
{
    uint8_t mode = get_timer2_mode();
    timer_clock_divider_t divider =  get_timer2_clock_divider();
    uint16_t ticks_count = 0;
    
    uart1_init(9600); // reinit uart because timer2 is used for uart timings
    printf_tiny(
        "Timer mode is %u, divider is %u and ticks count is %u\r\n", 
        mode, 
        divider,
        ticks_count
    );
}

void main()
{
    while(1)
    {
        timer2_mode0_12T_init();
        print_timer2_configs();
        
        timer2_mode0_1T_init();
        print_timer2_configs();

        delay_ms(1000);
    }
}
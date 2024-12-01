#include <sys.h>
#include <timer_common.h>
#include <timer2_mode0.h>

#include <delay.h>

#include <uart.h>
#include <stdio.h>

void print_timer2_mode_and_divider()
{
    uint8_t mode = get_timer2_mode();
    timer_clock_divider_t divider =  get_timer2_clock_divider();
    
    uart1_init(9600); // reinit uart because timer2 is used for uart timings
    printf_tiny("Timer mode is %d and divider is %d\n", mode, divider);
}

void timerISR() __interrupt(12)
{
    
}

void main()
{
    timer2_mode0_12T_init();
    print_timer2_mode_and_divider();
    
    timer2_mode0_1T_init();
    print_timer2_mode_and_divider();

    delay_ms(1000);
}
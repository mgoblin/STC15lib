#include <sys.h>
#include <timer.h>
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
        printf_tiny("Timer mode is %d\n", mode);

        timer0_mode1_12T_init();
        mode = get_timer0_mode();
        printf_tiny("Timer mode is %d\n", mode);

        LED = !LED;
        delay_ms(1000);
    }
}
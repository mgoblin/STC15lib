#include <sys.h>
#include <timer.h>
#include <delay.h>
#include <uart.h>

#include <stdio.h>

#define LED P10

void main()
{
    while (1)
    {
        timer2_mode0_12T_init();
        uint8_t mode = get_timer0_mode();
        
        uart_init(9600); // reinit uart because timer2 is used for uart timings
        printf_tiny("Timer mode is %d\n", mode);

        delay_ms(500);

        LED = !LED;
        
    }
}
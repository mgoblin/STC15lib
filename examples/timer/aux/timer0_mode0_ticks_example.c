#include <timer0_mode0.h>
#include <timer_to_ms.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define LED P10

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    uint16_t ticks = timer_frequency_to_ticks(2500);

    uart_init(9600);

    timer0_mode0_12T_init();
    timer0_mode0_enable_P35_output(true);
    timer0_mode0_start(ticks);

    while(1) 
    {
        delay_ms(300);
        printf_tiny("Ticks is 0x%x\n", ticks);
    }
}
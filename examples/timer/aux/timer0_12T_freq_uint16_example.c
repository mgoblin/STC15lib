#include <timer0_to_ms.h>

#include <frequency.h>
#include <delay.h>
#include <uart.h>
#include <stdio.h>
#include <stdlib.h>

#define LED P10
#define TICKS 0xffff

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{    
    timer0_mode0_12T_init();
    timer0_mode0_enable_P35_output(true);

    set_frequency_divider_scale(7);
    uint32_t timer_frequency = timer0_uint16_ticks_to_freq100(TICKS);
    set_frequency_divider_scale(0);

    char fstr[32];
    __ultoa(timer_frequency, fstr, 10);

    uart_init(9600);

    timer0_mode0_start(TICKS);
    
    while (1) {
        delay_ms(300);
        printf_tiny("Frequency: %s / 100 Hz\n", fstr);
    }
}
#include <timer0_mode0.h>
#include <timer_to_ms.h>

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
    // 64 628 = 0xFC74

    uart_init(9600);

    timer0_mode0_12T_init();
    timer0_mode0_enable_P35_output(true);
    timer0_mode0_start(TICKS);
    
    uint32_t timer_frequency = timer0_mode0_to_freq(TICKS);

    char fstr[32];

    __ultoa(timer_frequency, fstr, 10);

    while (1) {
        delay_ms(300);
        printf_tiny("Frequency: %s Hz\n", fstr);
    }
}
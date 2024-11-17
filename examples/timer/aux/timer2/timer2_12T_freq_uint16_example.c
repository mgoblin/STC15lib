#include <timer0_to_ms.h>

#include <frequency.h>
#include <delay.h>
#include <uart.h>
#include <stdio.h>
#include <stdlib.h>

#define LED P10
#define TICKS 0 //0xffff

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{    
    timer2_mode0_12T_init();
    timer2_mode0_enableP30_output(true);

    set_frequency_divider_scale(7);
    uint32_t timer_frequency = timer2_uint16_ticks_to_freq100(TICKS);
    set_frequency_divider_scale(0);

    char fstr[32];
    __ultoa(timer_frequency, fstr, 10);

    uart_init(9600);
    while (1) {
        delay_ms(200);
        // For TICKS = 0xffff and mcu clock divider 128 print 5 / 100 Hz
        // For TICKS = 0x0000 and mcu clock divider 128 print 360000 / 100 Hz 
        printf_tiny("Frequency: %s / 100 Hz\n", fstr);
    }
}
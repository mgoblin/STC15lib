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
    set_frequency_divider_scale(7);

    timer0_mode0_12T_init();
    timer0_mode0_enable_P35_output(true);

    uint32_t timer_frequency = timer0_uint16_ticks_to_freq100(TICKS);

    char fstr[32];
    __ultoa(timer_frequency, fstr, 10);

    uart1_init(9600);

    timer0_mode0_start(TICKS);
    
    while (1) {
        delay_ms(200);
        // For TICKS = 0xffff and mcu clock divider 128 print 5 / 100 Hz
        // For TICKS = 0x0000 and mcu clock divider 128 print 360000 / 100 Hz 
        printf_tiny("Frequency: %s / 100 Hz\n", fstr);
    }
}
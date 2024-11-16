#include <timer0_mode0.h>
#include <timer0_to_ms.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#include <stdlib.h>

#define LED P10

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{
    timer0_mode0_12T_init();
    timer0_mode0_enable_P35_output(true);

    set_frequency_divider_scale(1);
    uint16_t ticks = timer0_frequency_to_ticks_unsafe(2500);
    uint8_t freq_divider = get_frequency_divider();
    uint32_t freq = timer0_uint16_ticks_to_freq100(ticks);
    set_frequency_divider_scale(0);
    
    timer0_mode0_start(ticks);

    char fstr[32];
    __ultoa(freq, fstr, 10);

    uart_init(9600);
    while(1) 
    {
        delay_ms(300);
        printf_tiny("Ticks for 2500 Hz and freq_divider %u is 0x%x\n", freq_divider, ticks);
        printf_tiny("Vice versa 100 * frequency is %s\n", fstr);
    }
}
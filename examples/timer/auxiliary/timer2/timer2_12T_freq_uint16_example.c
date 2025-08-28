/** 
 * How to calculate timer2 frequency for timer ticks count
 * 
 * Timer2 use for uart1 and example can output timer signal 
 * to P3.0 or print frequency to UART1
 */
#include <timer2_to_ms.h>

#include <frequency.h>
#include <delay.h>
#include <uart.h>
#include <stdio.h>
#include <stdlib.h>

#define LED P10
#define TICKS 0xffff

void timerISR() __interrupt(12)
{
    LED = !LED;
}

void main()
{    
    set_frequency_divider_scale(7);

    timer2_mode0_12T_init();
    timer2_mode0_enable_P30_output();
    
    volatile uint32_t timer_frequency = timer2_uint16_ticks_to_freq100(TICKS);

    // timer2_mode0_start(TICKS);
    // while (1){}
    
    char fstr[32];
    __ultoa(timer_frequency, fstr, 10);

    uart1_init(1200);
    while (1) {
        delay_ms(200);
        // For TICKS = 0xffff and mcu clock divider 128 print 10 / 100 Hz
        // For TICKS = 0x0000 and mcu clock divider 128 print 720000 / 100 Hz 
        printf_tiny("Frequency: %s / 100 Hz\r\n", fstr);
    }
}
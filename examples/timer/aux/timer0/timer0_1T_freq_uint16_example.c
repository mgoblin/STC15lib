/**
 * How to calculate timer frequency and output timer signal 
 * to P35 signal 
 */
#include <timer0_to_ms.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define LED P10
#define TICKS 0x0000 // uint16 modify to change timer frequency

void timerISR() __interrupt(1)
{
    LED = !LED;
}

void main()
{    
    uart1_init(9600);
    
    timer0_mode0_1T_init();
    timer0_mode0_enable_P35_output(true);

    // For ticks = 0xffff calc result is 84.37 Hz, measurament is 84.517 Hz
    // For ticks = 0x0000 calc result is 5.529600 MHz, measurament is 5.538 MHz
    volatile uint32_t timer_frequency = timer0_uint16_ticks_to_freq100(TICKS);

    timer0_mode0_start(TICKS);

    while (1) 
    {
       printf_fast("100 * timer frequency is %lu Hz\n", timer_frequency); 
       delay_ms(100);
    }
}
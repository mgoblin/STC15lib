#include <timer0_mode0.h>
#include <timer_to_ms_common.h>

#include <uart.h>
#include <stdio.h>

#define LED P10

void timerISR() __interrupt(1)
{
}

void main()
{
    timer0_mode0_1T_init();
    timer0_mode0_enable_P35_output(true);

    uint16_t ticks = timer_ms_to_ticks(3, T1);
    timer0_mode0_start(ticks);   
    
    uart1_init(9600);
    while (1) 
    {
        printf_tiny("Ticks is %x\n", ticks);
    }
}
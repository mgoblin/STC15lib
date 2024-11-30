/** 
 * How to calculate P3.0 HIGH time ms for timer2
 * 
 * Timer2 used by UART1. 
 * Either print or P3.0 signal with calculated ms can be used
 *
 */
#include <timer2_to_ms.h>
#include <timer2_mode0.h>

#include <uart.h>
#include <stdio.h>

#define LED P10

#define TICKS 0xffff

void timerISR() __interrupt(12)
{
   LED = !LED;
}

void main()
{
   timer2_mode0_1T_init();
   timer2_mode0_enable_P30_output(true);
   
   volatile uint32_t ms = timer2_ticks_to_ms_usafe(TICKS);

   // timer2_mode0_start(TICKS);
   // while(1) {}

   uart1_init(9600);
   while (1) {
        printf_fast("P30 time is %lu ms\n", ms);
   }
}
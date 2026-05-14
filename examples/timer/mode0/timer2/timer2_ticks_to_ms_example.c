/**
 * @file timer2_ticks_to_ms_example.c
 * 
 * How to calculate P3.0 HIGH time ms for timer2
 * 
 * Timer2 used by UART1. 
 * Either print or P3.0 signal with calculated ms can be used
 *
 */
#include <timer2_mode0_to_ms.h>
#include <timer2_mode0.h>

#include <uart.h>
#include <stdio.h>

/// LED pin 
#define LED P10

/// Timer2 ticks count
#define TICKS 0xffff

/**
 * @brief interrupt request handler
 */
void timerISR() __interrupt(INTERRUPT_TIMER2)
{
   LED = !LED;
}


/// @brief  Entry point
void main()
{
   timer2_mode0_1T_init();
   timer2_mode0_enable_P30_output();
   
   volatile uint32_t ms = timer2_mode0_ticks_to_ms(TICKS);

   // timer2_mode0_start(TICKS);
   // while(1) {}

   uart1_init(9600);
   while (1) {
        printf_fast("P30 time is %lu ms\r\n", ms); // 5ms
   }
}
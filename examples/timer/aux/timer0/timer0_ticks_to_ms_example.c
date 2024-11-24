#include <timer0_to_ms.h>
#include <timer2_mode0.h>

#include <uart.h>
#include <stdio.h>

#define TICKS 0xffff

void main()
{
   set_frequency_divider_scale(1);

   uart1_init(9600);

   timer0_mode0_1T_init();
   timer0_mode0_enable_P35_output(true);
   
   timer0_mode0_start(TICKS);

   uint32_t ms = timer_ticks_to_ms_usafe(TICKS, get_timer0_clock_divider(), get_frequency_divider());

   while (1) {
        printf_fast("P35 time is %lu ms\n", ms);
   }
}
#include <timer2_to_ms.h>
#include <timer2_mode0.h>

#include <uart.h>
#include <stdio.h>

#define TICKS 0xffff

void main()
{
   timer2_mode0_1T_init();
   
   uint32_t ms = timer2_ticks_to_ms_usafe(TICKS);

   uart1_init(9600);
   while (1) {
        printf_fast("P35 time is %lu ms\n", ms);
   }
}
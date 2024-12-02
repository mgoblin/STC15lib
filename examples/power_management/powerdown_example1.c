#include <power_management.h>

#include <uart.h>
#include <stdio.h>

void main()
{
    uart1_init(9600);
    wakeup_timer_init(0xffff); // 0x7fff 

    while (1)
    {
        printf_tiny("WKTCH = 0x%x, WKTCL = 0x%x\n", WKTCH, WKTCL);
    }
}
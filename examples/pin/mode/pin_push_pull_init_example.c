/**
 * How to init pin (P14) in push-pull mode
 */

#include <pin.h>

#include <uart.h>
#include <stdio.h>

void main()
{
    P1M0 = 0x00;
    P1M1 = 0xff;

    pin_push_pull_init(P1, 4);

    uart1_init(9600);

    while (1)
    {
        printf_tiny("P1M0 = 0x%x, P1M1 = 0x%x\n", P1M0, P1M1);
    }
    
}
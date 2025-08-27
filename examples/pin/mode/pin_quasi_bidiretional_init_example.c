/**
 * How to init pin (P31) in quasi bidiretional mode
 */
#include <pin.h>

#include <uart.h>
#include <stdio.h>

void main()
{
    P3M1 = 0xff;
    P3M0 = 0xff;

    pin_quasi_bidiretional_init(P3, 1);

    uart1_init(9600);

    while (1)
    {
        printf_tiny("PxM1 = 0x%x, PxM0 = 0x%x\r\n", P3M1, P3M0); // P3M1 = P3M0 = 0xFD
    }
}
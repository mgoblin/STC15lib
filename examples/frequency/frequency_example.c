#include <sys.h>
#include <frequency.h>
#include <uart.h>
#include <delay.h>
#include <bits.h>

#include <stdio.h>

#define LED P10

void main()
{
    uart_init(9600);

    update_and_get_frequency_divider(7); // set system clock value to master clock / 128

    while (1)
    {
        //printf_tiny("Master clock freq is %d", get_master_clock_frequency_high_part());
        //printf_tiny("%d Hz\n", get_master_clock_frequency_low_part());
        //printf_tiny("Master clock divider is %d\n", get_frequency_divider());

        LED = 1;
        delay_ms(500);
        LED = 0;
        delay_ms(500);
    }
}
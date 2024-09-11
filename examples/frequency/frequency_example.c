#include <sys.h>
#include <frequency.h>
#include <delay.h>
#include <uart.h>

#include <stdio.h>

#define LED P10

void main()
{
    update_and_get_frequency_divider(7); // set system clock value to master clock / 128

    while (1)
    {
        LED = !LED;
        delay_ms(500); // but delay still 500 ms because delay know about frequency divider
    }
}
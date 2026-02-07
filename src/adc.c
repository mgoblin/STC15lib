#include <adc.h>

#include <stdio.h>
#include <uart.h>

void adc_init(void)
{
}

void adc_start(void)
{
}

uint16_t adc_read(void)
{
    return 0;
}

void main(void)
{
    adc_init();
    adc_start();

    uart1_init(9600);

    while (1)
    {
        uint16_t result = adc_read();
        printf_tiny("ADC result is %d\r\n", result);
    }
}
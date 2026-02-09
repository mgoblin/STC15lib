#include <adc.h>

#include <stdio.h>
#include <uart.h>

#define p1_pin 1

void main(void)
{
    uart1_init(9600);

    adc_init(p1_pin, PIN_INPUT_ONLY,false, ADC_SPEED_90);

    while (1)
    {
        uint16_t result; 
        adc_read(&result);
        printf_tiny("ADC result is %x\r\n", result);
    }

    adc_destroy();
}
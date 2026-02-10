/** How to read ADC value in main loop */

#include <adc.h>

#include <stdio.h>
#include <uart.h>

// ADC pin P1.1
#define p1_pin 1

void main(void)
{
    uart1_init(9600);

    // Init ADC on P1.1 on maximum speed
    adc_init(p1_pin, PIN_INPUT_ONLY,false, ADC_SPEED_90);

    while (1)
    {
        uint16_t result; 
        adc_read(&result);
        printf_tiny("ADC result is %x\r\n", result);
    }

}
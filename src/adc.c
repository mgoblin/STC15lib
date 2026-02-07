#include <adc.h>

#include <gpio.h>

#include <stdio.h>
#include <uart.h>

#define ADC_START_BIT 3
#define ADC_FLAG 4
#define ADRJ_BIT 5

void adc_init(uint8_t p1_pin)
{
    pin_input_only_init(P1, p1_pin);
    ADC_CONTR = 0x80 + p1_pin;

    // TODO Set speed
    // TODO ADRJ
}

uint16_t adc_read(void)
{
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG));
    bit_set(ADC_CONTR, 1 << ADC_START_BIT);
    
    while (test_if_bit_cleared(ADC_CONTR, 1 << ADC_FLAG));
    
    uint16_t adc_value =  test_if_bit_set(CLK_DIV, 1 << ADRJ_BIT) ?
        (ADC_RESL << 2) | (ADC_RES & 0x03) : (ADC_RES << 2) | (ADC_RESL & 0x03);

    return adc_value;
}


#define p1_port 1 

void main(void)
{
    uart1_init(9600);
    adc_init(p1_port);

    while (1)
    {
        uint16_t result = adc_read();
        printf_tiny("ADC result is %x\r\n", result);
    }
}
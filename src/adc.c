#include <adc.h>

#include <gpio.h>

#include <stdio.h>
#include <uart.h>

#define ADC_START_BIT 3
#define ADC_FLAG 4
#define ADRJ_BIT 5

void adc_init(adc_config_t *config)
{
    pin_input_only_init(P1,config->p1_pin);
    ADC_CONTR = 0x80 | config->p1_pin;

    config->adrj_flag ? 
        bit_set(CLK_DIV, 1 << ADRJ_BIT) : 
        bit_clr(CLK_DIV, ~(1 << ADRJ_BIT)); 

    // TODO Set speed
}

uint16_t adc_read(void)
{
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG));
    bit_set(ADC_CONTR, 1 << ADC_START_BIT);

    while (test_if_bit_cleared(ADC_CONTR, 1 << ADC_FLAG));
    
    return test_if_bit_set(CLK_DIV, 1 << ADRJ_BIT) ?
        (ADC_RESL << 2) | (ADC_RES & 0x03) : (ADC_RES << 2) | (ADC_RESL & 0x03);
}


#define p1_port 1

void main(void)
{
    uart1_init(9600);

    const adc_config_t adc_config = 
    {
        .p1_pin = 1, 
        .adrj_flag = false,
        .speed = 0
    };

    adc_init(&adc_config);

    while (1)
    {
        uint16_t result = adc_read();
        printf_tiny("ADC result is %x\r\n", result);
    }
}
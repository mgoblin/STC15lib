#include <adc.h>

#include <gpio.h>

#include <stdio.h>
#include <uart.h>

#define ADC_START_BIT 3
#define ADC_FLAG 4
#define ADRJ_BIT 5

#define ADC_POWER_ON_MSK 0x80
#define ADC_LOW_BITS_COUNT 2
#define ADC_LOW_BITS_MSK 0x03

void adc_init(uint8_t p1_pin, adc_pin_mode_t pin_mode, bool adrj_flag, uint8_t speed)
{
    switch (pin_mode)
    {
        case PIN_OPEN_DRAIN:
            pin_open_drain_init(P1, p1_pin);
            break;
        
        case PIN_INPUT_ONLY:
            pin_input_only_init(P1,p1_pin);
            break;
    
        default:
            pin_input_only_init(P1,p1_pin);
            break;
    };
    
    // TODO Set P1ASF bits

    ADC_CONTR = ADC_POWER_ON_MSK | p1_pin;

    adrj_flag ? 
        bit_set(CLK_DIV, 1 << ADRJ_BIT) : 
        bit_clr(CLK_DIV, ~(1 << ADRJ_BIT)); 

    // TODO Set speed
    // For disable unsed argument warning
    speed;
}

uint16_t adc_read(void)
{
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG));
    bit_set(ADC_CONTR, 1 << ADC_START_BIT);

    while (test_if_bit_cleared(ADC_CONTR, 1 << ADC_FLAG));
    
    return test_if_bit_set(CLK_DIV, 1 << ADRJ_BIT) ?
        (ADC_RESL << ADC_LOW_BITS_COUNT) | (ADC_RES & ADC_LOW_BITS_MSK) 
        : 
        (ADC_RES << ADC_LOW_BITS_COUNT)  | (ADC_RESL & ADC_LOW_BITS_MSK);
}

void adc_destroy(uint8_t p1_pin)
{
    // For disable unsed argument warning
    p1_pin;
}

#define p1_pin 1

void main(void)
{
    uart1_init(9600);

    adc_init(p1_pin, PIN_INPUT_ONLY,false, 0);

    while (1)
    {
        uint16_t result = adc_read();
        printf_tiny("ADC result is %x\r\n", result);
    }

    adc_destroy(p1_pin);
}
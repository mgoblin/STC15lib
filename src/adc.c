#include <adc.h>

#include <gpio.h>

#define ADC_POWER_ON_MSK 0x80

#define ADC_LOW_BITS_COUNT 2
#define ADC_LOW_BITS_MSK 0x03

uint16_t adc_read(void)
{
    /* Clear ADC result ready flag */
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT));
    /* Set ADC power on */
    bit_set(ADC_CONTR, 1 << ADC_START_BIT);

    /* Waiting for ADC result is ready */
    while (test_if_bit_cleared(ADC_CONTR, 1 << ADC_FLAG_BIT));
    
    /* Return ADC result value */
    return test_if_bit_set(CLK_DIV, 1 << ADRJ_BIT) ?
        (ADC_RESL << ADC_LOW_BITS_COUNT) | (ADC_RES & ADC_LOW_BITS_MSK) 
        : 
        (ADC_RES << ADC_LOW_BITS_COUNT)  | (ADC_RESL & ADC_LOW_BITS_MSK);
}

void adc_destroy(void)
{
    /* Stop ADC */
    bit_clr(ADC_CONTR, ~(1 << ADC_START_BIT));
    /* Clear ADC result ready flag */
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT));

    /* Set all gpio P1 port pins as general purpose pins mode */
    P1ASF = 0;
}

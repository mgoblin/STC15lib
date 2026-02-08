#include <adc.h>

#include <gpio.h>

#define ADC_START_BIT 3
#define ADC_FLAG 4
#define ADRJ_BIT 5

#define ADC_POWER_ON_MSK 0x80
#define ADC_LOW_BITS_COUNT 2
#define ADC_LOW_BITS_MSK 0x03

void adc_init(uint8_t p1_pin, adc_pin_mode_t pin_mode, bool adrj_flag, adc_speed_t speed)
{
    /* Set input only or open drain pin mode according to pin_mode argument */
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
    
    /* Set P1ASF bit for using pin as ADC input */
    bit_set(P1ASF, 1 << p1_pin);

    /* Set ADC power on, speed and source channel pin */
    ADC_CONTR = ADC_POWER_ON_MSK | p1_pin | speed;

    /* Set ADC_RES-ADC_RESL or ADC_RESL-ADC_RES result bits order */
    if (adrj_flag)
    { 
        bit_set(CLK_DIV, 1 << ADRJ_BIT);
    }
    else
    {
        bit_clr(CLK_DIV, ~(1 << ADRJ_BIT)); 
    }
}

uint16_t adc_read(void)
{
    /* Clear ADC result ready flag */
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG));
    /* Set ADC power on */
    bit_set(ADC_CONTR, 1 << ADC_START_BIT);

    /* Waiting for ADC result is ready */
    while (test_if_bit_cleared(ADC_CONTR, 1 << ADC_FLAG));
    
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
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG));

    /* Set all gpio P1 port pins as general purpose pins mode */
    P1ASF = 0;
}

#include <adc.h>

#include <gpio.h>

void adc_destroy(void)
{
    /* Stop ADC */
    bit_clr(ADC_CONTR, ~(1 << ADC_START_BIT));
    /* Clear ADC result ready flag */
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT));

    /* Set all gpio P1 port pins as general purpose pins mode */
    P1ASF = 0;
}

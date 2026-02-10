#include <adc.h>

#define ADC_P0_PIN 1

void main(void)
{
    adc_init_input_only(ADC_P0_PIN, false, ADC_SPEED_90);

    while (1);
}
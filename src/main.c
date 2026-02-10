#include <adc.h>
#include <interrupt.h>
#include <delay.h>


#define ADC_P0_PIN 1
#define LED P10

uint16_t adc_async_get_result(void)
{
    return test_if_bit_set(CLK_DIV, 1 << ADRJ_BIT) ?  
        (ADC_RESL << ADC_LOW_BITS_COUNT) | (ADC_RES & ADC_LOW_BITS_MSK)  
        :                                               
        (ADC_RES << ADC_LOW_BITS_COUNT)  | (ADC_RESL & ADC_LOW_BITS_MSK);
}

void adc_async_read_finish(void)
{
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT));
}

void adc_ISR(void) __interrupt(5)
{
    if (adc_async_get_result())
    {
        LED = !LED;
    }
    adc_async_read_finish();
}

void main(void)
{
    adc_init_input_only(ADC_P0_PIN, false, ADC_SPEED_90);

    enable_mcu_interrupts();
    enable_adc_interrupt();

    while (1)
    {
        adc_async_read_start();
        delay_ms(1000);
    }
}
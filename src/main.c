#include <adc.h>
#include <interrupt.h>
#include <delay.h>


#define ADC_P0_PIN 1
#define LED P10

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
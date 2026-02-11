/**
 * How to use ADC in async mode example.
 * 
 * In main program thread adc is initialized 
 * and periodically run async reading.
 * 
 * After ADC result is ready adc_ISR will be called.
 * 
 * If ADC value is greater than 0 LED will be blinked.
 */

#include <adc.h>
#include <interrupt.h>
#include <delay.h>

// ADC pin P1.1
#define ADC_P0_PIN 1
// LED pin P1.0
#define LED_PIN P10

// READ interval
#define READ_INTERVAL 1000

/*
* ADC interrupt handler
*
* Read ADC value and if it greater than 0 change LED state 
*/
void adc_ISR(void) __interrupt(5)
{
    if (adc_async_get_result())
    {
        LED_PIN = !LED_PIN;
    }
    adc_async_read_finish();
}

void main(void)
{
    // Init ADC
    adc_init_input_only(ADC_P0_PIN, false, ADC_SPEED_90);

    // Enable ADC interrupt
    enable_mcu_interrupts();
    enable_adc_interrupt();

    while (1)
    {
        // Start async read. Result is handled in adc_ISR
        adc_async_read_start();
        delay_ms(READ_INTERVAL);
    }
}


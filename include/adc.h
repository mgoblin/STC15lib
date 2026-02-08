#ifndef STC15_ADCH
#define STC15_ADCH

#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

typedef enum 
{
    PIN_INPUT_ONLY,
    PIN_OPEN_DRAIN
} adc_pin_mode_t;

typedef enum 
{
    ADC_SPEED_540 = 0b00000000,
    ADC_SPEED_360 = 0b00100000,
    ADC_SPEED_180 = 0b01000000,
    ADC_SPEED_90  = 0b01100000
} adc_speed_t;

void adc_init(uint8_t p1_pin, adc_pin_mode_t pin_mode, bool adrj_flag, adc_speed_t speed);
uint16_t adc_read(void);
void adc_destroy(void);

#endif
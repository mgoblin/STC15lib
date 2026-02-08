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

void adc_init(uint8_t p1_pin, adc_pin_mode_t pin_mode, bool adrj_flag, uint8_t speed);
uint16_t adc_read(void);
void adc_destroy(uint8_t p1_pin);

#endif
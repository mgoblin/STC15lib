#ifndef STC15_ADCH
#define STC15_ADCH

#include <sys.h>
#include <bits.h>
#include <stdint.h>

void adc_init(uint8_t p1_pin);
void adc_start(void);
uint16_t adc_read(void);

#endif
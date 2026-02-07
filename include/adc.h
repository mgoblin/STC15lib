#ifndef STC15_ADCH
#define STC15_ADCH

#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

void adc_init(void);
void adc_start(void);
uint16_t adc_read(void);

#endif
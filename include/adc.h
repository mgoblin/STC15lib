#ifndef STC15_ADCH
#define STC15_ADCH

#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

typedef struct {
    uint8_t p1_pin : 3;
    bool adrj_flag : 1;
    uint8_t speed : 2;
} adc_config_t;

void adc_init(adc_config_t *config);
void adc_start(void);
uint16_t adc_read(void);

#endif
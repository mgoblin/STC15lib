#ifndef STC15_COUNTER0_MODE0H
#define STC15_COUNTER0_MODE0H

#include <stdint.h>

#include <interrupt.h>

#define T0 P34

void counter0_mode0_init();
void counter0_mode0_start();
void counter0_mode0_stop();
void counter0_mode0_set_value(uint16_t value);
uint16_t counter0_mode0_get_value();

#endif
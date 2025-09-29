#ifndef STC15_UART1MODE1H
#define STC15_UART1MODE1H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <interrupt.h>
#include <timer2_mode0.h>

void uart1_mode1_timer2_init();

void uart1_mode1_timer2_start(const uint32_t baudrate);
void uart1_mode1_timer2_stop();

#endif
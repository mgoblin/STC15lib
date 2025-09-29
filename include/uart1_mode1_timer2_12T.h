#ifndef STC15_UART1MODE1H
#define STC15_UART1MODE1H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <timer2_mode0.h>

typedef enum 
{
    RxD_P30_TxD_P31 = 0x00,
    RxD_P36_TxD_P37 = 0x40,
    RxD_P16_TxD_P17 = 0x80,

} uart1_pins_t;

void uart1_mode1_timer2_init(uart1_pins_t pins);

void uart1_mode1_timer2_start(const uint32_t baudrate);
void uart1_mode1_timer2_stop();

#endif
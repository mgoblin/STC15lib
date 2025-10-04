#ifndef STC15_UART1MODE1_T112_MODE0H
#define STC15_UART1MODE1_T112_MODE0H

#include <stdint.h>
#include <stdbool.h>

#include <sys.h>
#include <uart1_shared.h>

typedef enum
{
    baudtate_9600
} uart1_mode1_timer2_1T_baudrate_t;

void uart1_mode1_timer1_mode0_12T_init(uart1_pins_t pins);

void uart1_mode1_timer1_mode0_12T_start(uart1_mode1_timer2_1T_baudrate_t baudrate);

uint32_t uart1_mode1_timer1_mode0_12T_ticks(uart1_mode1_timer2_1T_baudrate_t baudrate);

void uart1_mode1_timer1_mode0_12T_start_ext(uart1_mode1_timer2_1T_baudrate_t baudrate);

void uart1_mode1_timer1_mode0_12T_stop();

bool is_uart1_mode1_timer1_mode0_12T_started();

#endif
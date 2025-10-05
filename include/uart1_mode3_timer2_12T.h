#ifndef STC15_UART1MODE3_T212H
#define STC15_UART1MODE3_T212H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <frequency.h>
#include <interrupt.h>
#include <uart1_shared.h>

typedef enum 
{
    /** @brief 1200 baudrate */
    baudrate_1200 = 0xFF3F,
    /** @brief 2400 baudrate */
    baudrate_2400 = 0xFF9F,
    /** @brief 4800 baudrate */
    baudrate_4800 = 0xFFCF,
    /** @brief 9600 baudrate */
    baudrate_9600 = 0xFFE7,
} uart1_mode2_timer2_12t_baudrate_t;

void uart1_mode3_timer2_12T_init(uart1_pins_t pins);

void uart1_mode3_timer2_12T_start(uart1_mode2_timer2_12t_baudrate_t baudrate);

#define uart1_mode3_timer2_12T_ticks(baudrate) (65536 - ((((MAIN_Fosc / 12) / baudrate) >> 2) >> get_frequency_divider_scale()))

void uart1_mode3_timer2_12T_start_ext(uart1_mode2_timer2_12t_baudrate_t baudrate);

#define uart1_mode3_timer2_12T_stop (bit_clr(AUXR, CBIT4))

#define is_uart1_mode3_timer2_12T_started() (test_if_bit_set(AUXR, SBIT4))

#endif
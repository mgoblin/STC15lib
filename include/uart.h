#pragma once

/**
 * @file uart.h
 * @defgroup uart UART serial interface
 * @details Functions and data structures related to exchange data thru UART
 * @author Michael Golovanov
 */

#include <stdint.h>

/**
 * @brief Initiazlize UART
 * 
 * @ingroup uart
 */
void uart_init(uint32_t uart_baudrate);
void uart_send_byte(uint8_t data);
uint8_t uart_receive_byte();

int putchar(int ch);
int getchar(void);

#pragma once

/**
 * @file uart.h
 * @defgroup uart UART1
 * @details Functions and data structures related to exchange data thru UART1
 * @author Michael Golovanov
 */
#include <sys.h>
#include <stdint.h>
#include <timer2_mode0.h>
#include <timer2_to_ms.h>

/**
 * @brief Initiazlize UART1
 * 
 * @details Initialize uart using Timer2. Set timer according to baudrate
 * 
 * @param uart_baudrate uint32_t uart baudrate, like 9600 and etc
 * 
 * 
 * @ingroup uart
 */
#define uart1_init(uart_baudrate)                                       \
do {                                                                    \
    SCON = 0x50; /* Set Mode1: 8-Bit UART with Variable Baud Rate */    \
    timer2_mode0_reload(timer2_mode0_baudrate_to_ticks(uart_baudrate)); \
    AUXR &= 0xE2;                                                       \
    AUXR |= 0x15;                                                       \
} while(0)

/**
 * Send byte to UART
 * 
 * @param data byte to send
 * 
 * @ingroup uart
 */
void uart1_send_byte(uint8_t data);

/**
 * @brief Receive byte from UART1
 * 
 * @details This receive is implemented as synhcronous operation. 
 * Waiting until byte is received 
 * 
 * @return received byte
 * 
 * @ingroup uart
 */
uint8_t uart1_receive_byte();

/**
 * @brief Send character to UART1
 * @details This method need for printf
 * 
 * @param ch character to send
 * 
 * @return char sended to UART 
 * 
 * @ingroup uart
 */
int putchar(int ch);

/**
 * @brief Receive character from UART1
 * @details This method need for scanf
 * 
 * @return received char
 * 
 * @ingroup uart
 */
int getchar(void);

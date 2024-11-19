#pragma once

/**
 * @file uart.h
 * @defgroup uart UART serial interface
 * @details Functions and data structures related to exchange data thru UART
 * @author Michael Golovanov
 */
#include <sys.h>
#include <stdint.h>

/**
 * @brief Initiazlize UART1
 * 
 * @details Initialize uart using Timer2. Set timer according to baudrate
 * 
 * @param uart_baudrate uart baudrate, like 9600 and etc
 * 
 * @ingroup uart
 */
void uart1_init(uint32_t uart_baudrate);

/**
 * Send byte to UART
 * 
 * @param data byte to send
 * 
 * @ingroup uart
 */
void uart_send_byte(uint8_t data);

/**
 * @brief Receive byte from UART
 * 
 * @details Tihs receive is implemented as synhcronous operation. 
 * Waiting until byte is received 
 * 
 * @return received byte
 * 
 * @ingroup uart
 */
uint8_t uart_receive_byte();

/**
 * @brief Send character to UART
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
 * @brief Receive character from UART
 * @details This method need for scanf
 * 
 * @return received char
 * 
 * @ingroup uart
 */
int getchar(void);

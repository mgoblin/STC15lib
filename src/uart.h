#pragma once

/**
 * @file uart.h
 * @defgroup uart Simple UART1
 * @details Functions and data structures related to exchange data thru UART1
 * 
 * @see uart1_send_byte()
 * @see uart1_receive_byte()
 * @see is_uart1_send_byte_complete()
 * @see is_uart1_receive_byte_complete()
 * 
 * @author Michael Golovanov
 */
#include <sys.h>
#include <stdint.h>
#include <uart1_mode1_timer2_1T.h>
#include <uart1_shared.h>

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
    uart1_mode1_timer2_1T_init(RxD_P30_TxD_P31);                        \
    uart1_mode1_timer2_1T_start_ext(uart_baudrate);                     \
} while(0)

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

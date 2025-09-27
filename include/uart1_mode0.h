#ifndef STC15_UART1MODE0H
#define STC15_UART1MODE0H
/**
 * @file uart1_mode0.h
 * @defgroup uart1_mode0 UART1 Mode 0
 * @details Functions and data structures for UART1 communication in Mode 0.
 * 
 * Mode 0 provides synchronous communication with fixed baud rate.
 * 
 * @author Michael Golovanov
 * 
*/

/** @name init
 *  UART1 initializaion functions
 */
///@{

/**
 * @brief Initializes UART1 in Mode 0.
 * 
 * Must be called before any UART communication is initiated.
 * 
 * @note Assumes system clock is already configured.
 * @note Modifies UART1 control and status registers.
 * 
 * @ingroup uart1_mode0
 */
void uart1_mode0_init();

///@}

#endif
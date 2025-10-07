#ifndef STC15_UART1SHAREDH
#define STC15_UART1SHAREDH

/**
 * @file uart1_shared.h
 * 
 * @defgroup uart1_shared UART1 all modes
 * 
 * @details UART1 routines used in all UART1 modes.
 * 
 * This header file included in all UART1 mode headers and 
 * do not need to be included explicitly.
 * 
 * @author Michael Golovanov
 */

 /**
 * @brief UART1 RxD/TxD pins enum
 * 
 * @ingroup uart1_shared
 */
typedef enum 
{
    /** @brief RxD on P3.0 and TxD on P3.1 pins */
    RxD_P30_TxD_P31 = 0x00,
    /** @brief RxD on P3.6 and TxD on P3.7 pins */
    RxD_P36_TxD_P37 = 0x40,
    /** @brief RxD on P1.6 and TxD on P1.7 pins */
    RxD_P16_TxD_P17 = 0x80,

} uart1_pins_t;

#endif

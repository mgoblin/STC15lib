#ifndef STC15_RESETH
#define STC15_RESETH


#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @file reset.h
 * @defgroup mcu_reset Reset
 * @details Functions and data structures related software reset
 * 
 * @author Michael Golovanov
 */

/** @name reset
 *  MCU reset functions 
 */
///@{

/**
 * @brief Software reset
 * @details Restart MCU 
 * 
 * @ingroup mcu_reset
 */
#define reset() (bit_set(IAP_CONTR, SBIT5))

///@}

#endif

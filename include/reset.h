#ifndef STC15_RESETH
#define STC15_RESETH


#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @file reset.h
 * @defgroup mcu_reset Reset and WDT
 * @details Functions and data structures related software reset
 * 
 * WDT timings biased by MCU frequency change (frequency divider).
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
#define reset() (bit_set(IAP_CONTR, 5))

///@}

/** @name wdt
 *  Watchdog timer functions 
 */
///@{

/**
 * @brief Init WDT
 * @details WDT overflow time = (12 * wdt_scale * 32768) / MainFosc
 * 
 * @param wdt_scale uint8_t WDT timer scale in range 0..7 
 * 
 * @ingroup mcu_reset
 */
void wdt_init(uint8_t wdt_scale);

/**
 * @brief Start WDT
 * @details Call wdt_start after wdt_init call 
 * 
 * @ingroup mcu_reset
 */
void wdt_start();

/**
 * @brief Stop WDT
 * @details Call wdt_stop after wdt_init and wdt_start call 
 * 
 * @ingroup mcu_reset
 */
void wdt_stop();
bool is_wdt_started();
void wdt_clear();
bool is_wdt_flag_on();
void reset_wdt_flag();

///@}

#endif

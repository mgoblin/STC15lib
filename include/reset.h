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

/** @name watchdog timer
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

/**
 * @brief Get WDT start status
 * @details Call is_wdt_started after wdt_init call 
 * 
 * @return bool - true if WDT started and false if not
 * 
 * @ingroup mcu_reset
 */
bool is_wdt_started();

/**
 * @brief clear WDT to prevent restart
 * @details Call wdt_clear after wdt_start call to prevent WDT reset MCU
 * 
 * @ingroup mcu_reset
 */
void wdt_clear();

/**
 * @brief Get reset by WDT flag
 * @details WDT reset flag set after restart caused by WDT
 * 
 * @return bool true if MCU reset caused by WDT and false otherwise 
 * 
 * @ingroup mcu_reset
 */
bool is_wdt_flag_on();

/**
 * @brief Reset WDT flag
 * @details Reset WDT flag to false. 
 * 
 * @ingroup mcu_reset
 */
void reset_wdt_flag();

///@}

#endif

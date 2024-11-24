#ifndef STC15_RESETH
#define STC15_RESETH


#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @file reset.h
 * @defgroup reset Reset and WDT
 * @details Functions and data structures related software reset 
 * @author Michael Golovanov
 */

/**
 * @brief Software reset
 * @details Restart MCU 
 * 
 * @ingroup reset
 */
#define reset() (bit_set(IAP_CONTR, 5))

void wdt_init(uint8_t wdt_scale);
void wdt_start();
void wdt_stop();
bool is_wdt_started();
void wdt_reset();
bool is_wdt_flag_on();
void reset_wdt_flag();

#endif

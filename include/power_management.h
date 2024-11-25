#ifndef POWER_MANAGEMENTH
#define POWER_MANAGEMENTH

/**
 * @file power_management.h
 * @defgroup power_management Power management
 * @details Functions and data structures related for MCU power management
 * @author Michael Golovanov
 */


#include <sys.h>
#include <bits.h>

/**
 * @brief Set MCU idle mode
 * @details Shuts off 
 * clock to CPU, but clock to Timers, Interrupts, Serial Ports, and 
 * Analog Peripherals are still active  
 * 
 * @ingroup power_management
 */
#define idle() (bit_set(PCON, 0))

#endif
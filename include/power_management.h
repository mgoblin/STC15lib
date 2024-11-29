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
 * Analog Peripherals are still active. 
 * The CPU status is preserved in its entirety: 
 * the RAM, Stack Pointer, Program Counter, Program Status Word, 
 * Accumulator, and all other registers maintain their data during Idle. 
 * The port pins hold the logical states they had at the time Idle was activated.  
 * 
 * @ingroup power_management
 */
#define idle() (bit_set(PCON, SBIT0))

/**
 * @brief Set MCU power down mode
 * @details 
 * 
 * @ingroup power_management
 */
#define power_down() (bit_set(PCON, SBIT1))

#endif
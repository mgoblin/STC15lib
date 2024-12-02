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
#include <stdint.h>
#include <stdbool.h>

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
 * @details In the Stop/Power-Down mode, the on-chip oscillator 
 * and the Flash memory are stopped in order to minimize power consumption. 
 * Only the power-on circuitry will continue to draw power during Stop/Power-Down. 
 * The contents of on-chip RAM and SFRs are maintained.
 * 
 * @ingroup power_management
 */
#define power_down()            \
{                               \
    bit_set(PCON, SBIT1);       \
    __asm__("nop");             \
    __asm__("nop");             \
    __asm__("nop");             \
}

void wakeup_timer_init(uint16_t ticks);
void wakeup_timer_start();
void wakeup_timer_stop();
bool is_wakeup_timer_started();

#endif
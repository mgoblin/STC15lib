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
 * @brief Wakeup timer internal clock frequency value high byte address
 * 
 * @ingroup power_management
 */
#define WIRC_H_ADDRESS 0xf8

/**
 * @brief Wakeup timer internal clock frequency value low byte address
 * 
 * @ingroup power_management
 */
#define WIRC_L_ADDRESS 0xf9

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

/**
 * @brief Init and run wakeup timer
 * @details 
 * Wakeup time is calculated as (10^6/wakeup_timer_internal_clock_frequency) * 16 * ticks
 * 
 * @see wakeup_timer_internal_clk_freq()
 * 
 * @param ticks uint16_t wakeup timer ticks count
 * 
 * @ingroup power_management
 */
#define wakeup_timer_init(ticks)                        \
{                                                       \
    WKTCH = (ticks >> 8) | 0x80;                        \
    WKTCL = ticks & 0xff;                               \
}

static volatile __idata uint8_t * const wirc_h_ptr = (__idata uint8_t *) WIRC_H_ADDRESS;
static volatile __idata uint8_t * const wirc_l_ptr = (__idata uint8_t *) WIRC_L_ADDRESS;
/**
 * @brief Get wakeup timer internal clock frequency
 * 
 * @details wakeup timer internal clock frequency after MCU powerup is placed
 * in RAM __idata 0xf8-0xf9 adresses. 
 * 
 * By default SDCC compiler generate firmware part that before main() call
 * clear RAM and 0xf8-0xf9 contains 0x00 values.
 * 
 * To avoid memory clearing implement empty   
 * void _mcs51_genRAMCLEAR() {} routine. Otherwise routine call return result 0x00.
 * 
 * Default value is 0x8c0a = 35850Hz.
 * 
 * @return uint16_t wakeup timer internal clock frequency from 0xf8-0xf9 RAM 
 * 
 * @ingroup power_management
 */
#define wakeup_timer_internal_clk_freq() (((uint16_t)*wirc_h_ptr << 8) | *wirc_l_ptr)

#endif
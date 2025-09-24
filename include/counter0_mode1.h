#ifndef STC15_COUNTER0_MODE1H
#define STC15_COUNTER0_MODE1H

/**
 * @file counter0_mode1.h
 * @defgroup counter0_mode1 Counter0 Mode1
 * 
 * @details Counter0 mode 1 routines.
 * 
 * This module supports general purpose counter0.
 * Timer can work as COUNTER or TIMER.
 * 
 * Counter increments on T0 pin change state.
 * 
 * Counter0 Mode1 is 16-bit counter.
 * Mode1 is like mode0 but without reloading and P35 pin output features.
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <assert.h>

#include <interrupt.h>

 /**
 * @brief T0 pin definition
 * 
 * @ingroup counter0_mode1
 */
#define T0 P34


/** @name init
 *  Counter initializaion functions 
 */
///@{

/**
 * @brief Initialize mode1 for counter0.
 * 
 * @details Enable counter0 interrupt and set mode1.
 * 
 * Mode 1 is configured as setting TMOD lowest 4 bytes:
 * - TMOD.0 = 1
 * - TMOD.1 = 0
 * - TMOD.2 = 1
 * - TMOD.3 = 0
 * 
 * @attention Interrupt handler void counter0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * @ingroup counter0_mode1
 */
#define counter0_mode1_init()                   \
do {                                            \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
                                                \
    TMOD &= 0xF0;                               \
    TMOD |= 0x05;                               \
                                                \
    TF0 = 0;                                    \
    TR0 = 0;                                    \
} while(0)   

///@}

/** @name start/stop
 *  Counter0 start/stop functions 
 */
///@{

/**
 * @brief Starts Counter 0 in Mode 1 with a specified initial value.
 * 
 * @details Loads the initial 16-bit value into Counter 0 registers and starts the counter.
 * 
 * @attention Before calling this function, counter0_mode1_init() should be called.
 * 
 * @param value 16-bit unsigned integer specifying the initial counter count
 * 
 * @ingroup counter0_mode1
 */
#define counter0_mode1_start(value)             \
do {                                            \
    static_assert(value <= 0xffff, "value is too large"); \
                                                \
    const uint16_t _val = value;                \
    TH0 = (uint8_t) (_val >> 8);                \
    TL0 = (uint8_t) (_val & 0xFF);              \
                                                \
    TF0 = 0;                                    \
    TR0 = 1;                                    \
} while(0)

/**
 * @brief Check if counter0 is started
 * 
 * @return true if counter0 started otherwise false
 * 
 * @ingroup counter0_mode1
 * 
 */ 
#define is_counter0_mode1_started() (TR0 == 1)

/**
 * @brief Stop counter0
 * 
 * @details Stop counter0 and clear TF0 flag.
 * 
 * @ingroup counter0_mode1
 */
#define counter0_mode1_stop()                   \
do {                                            \
    TR0 = 0;                                    \
    TF0 = 0;                                    \
} while(0)

///@}

/** @name read
 *  Counter read value functions 
 */
///@{

/** 
 * @brief Get counter0 value in mode1
 * 
 * @return uint16_t counter value
 * 
 * @ingroup counter0_mode1
*/
#define counter0_mode1_get_value() ((((uint16_t) TH0) << 8) | TL0)
///@}

#endif

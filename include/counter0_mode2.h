#ifndef STC15_COUNTER0_MODE2H
#define STC15_COUNTER0_MODE2H

/**
 * @file counter0_mode2.h
 * 
 * @defgroup counter0_mode2 Counter0 Mode2
 * 
 * @details Counter0 mode 2 routines.
 * This module supports general purpose counter0.
 * Timer can work as COUNTER or TIMER.
 * 
 * Counter increments on T0 pin change state.
 * 
 * Counter0 Mode2 is 8-bit autoreloadable counter.
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <assert.h>

#include <interrupt.h>

/**
 * @brief T0 pin definition
 * 
 * @ingroup counter0_mode2
 */
#define T0 P34

/**
 * @brief INT0 pin definition
 * 
 * @ingroup counter0_mode2
 */
#define INT0 P32

/** @name init
 *  Counter initializaion functions 
 */
///@{

/**
 * @brief Initialize mode2 for counter0.
 * 
 * @details Enable counter0 interrupt and set mode2.
 * 
 * Mode2 is configured as setting TMOD lowest 4 bytes:
 * - TMOD.0 = 0
 * - TMOD.1 = 1
 * - TMOD.2 = 1
 * - TMOD.3 = 0
 * 
 * @attention Interrupt handler void counter0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * @ingroup counter0_mode2
 */
#define counter0_mode2_init()                   \
do {                                            \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
                                                \
    TMOD &= 0xF0;                               \
    TMOD |= 0x06;                               \
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
 * @brief Starts Counter 0 in Mode 2 with a specified initial value.
 * 
 * @details Loads the initial 8-bit value into Counter 0 registers and starts the counter.
 * 
 * @attention Before calling this function, counter0_mode2_init() should be called.
 * 
 * @param value 8-bit unsigned integer specifying the initial counter count
 * 
 * @ingroup counter0_mode2
 */
 #define counter0_mode2_start(value)            \
 do {                                           \
    static_assert(value <= 0xff, "value is too large"); \
                                                \
    TH0 = (uint8_t) value;                      \
                                                \
    TF0 = 0;                                    \
    TR0 = 1;                                    \
 } while(0)
 
 /**
 * @brief Stop counter0
 * @details Stop count T0 pin state changes. 
 * Before stop counter0_mode2_start should be called.
 * 
 * @ingroup counter0_mode2
 */
#define counter0_mode2_stop()                   \
do {                                            \
    TR0 = 0;                                    \
} while (0)

/**
 * @brief Get counter0 mode2 started status.
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup counter0_mode2
 */
#define is_counter0_mode2_started() (TR0 == 1 && (is_counter0_mode2_gate_opened() || INT0 == 1) )

///@}

/** @name read/write
 *  Counter get and set value functions 
 */
///@{

/**
 * @brief get counter0 value in mode2
 * 
 * @return uint8_t counter value
 * 
 * @ingroup counter0_mode2
 */
#define counter0_mode2_get_value() (TL0)

/**
 * @brief set counter0 value in mode2
 * 
 * @details Call this method before counter0 started.
 * 
 * @param value uint8_t counter value to set
 * 
 * @ingroup counter0_mode2
 */
#define counter0_mode2_set_value(value)         \
do {                                            \
    static_assert(value <= 0xff, "value is too large"); \
    TH0 = value;                                \
} while(0)

///@}

/** @name config
 *  Counter0 pin output and gate config functions 
 */
///@{

/**
 * @brief enable output to P3.5
 * 
 * @details Enable pin P.3.5 state changes on counter0 overflow.
 * By default P3.5 output is disabled
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode2_enable_P35_output()   (bit_set(INT_CLKO, SBIT0))


///@}

#endif

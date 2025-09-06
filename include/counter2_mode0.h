#ifndef STC15_COUNTER2_MODE0H
#define STC15_COUNTER2_MODE0H

/**
 * @file counter2_mode0.h
 * @defgroup counter2_mode0 Counter2 Mode0
 * @details Functions and data structures for counter2 mode0.
 * 
 * This module supports general purpose counter2.
 * Mode0 is auto reload 16-bit counter..
 * 
 * Counter2 increments its value on T0 pin change state from 0 to 1. 
 * Once the counter reaches its maximum value of 65535, 
 * the counter is reset to zero at the next increment. 
 * On counter overflow reset interrupt 1 is raised.
 * 
 * @author Michael Golovanov
*/
#include <assert.h>
#include <stdint.h>
#include <stdbool.h>

#include <interrupt.h>
#include <bits.h>

/**
 * @brief T2 pin definition
 * 
 * @ingroup counter2_mode0
 */
#define T2 P31

/** @name init
 *  Counter initializaion functions 
 */
///@{
/**
 * @brief Initialize mode0 for counter2. 
 * 
 * @details Enable counter2 interrupt and set mode0
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_init()                   \
do {                                            \
    enable_mcu_interrupts();                    \
    enable_timer2_interrupt();                  \
                                                \
    bit_clr(AUXR, CBIT4);                       \
    bit_set(AUXR, SBIT3); /* init Counter2 */   \
} while(0)
///@}

/** @name run
 *  Counter run/stop/reload functions 
 */
///@{

/**
 * @brief Run counter2.
 * 
 * @details Before run counter2_mode0_init should be called.
 * After run counter2 is counted T0 pin state change.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * @param value uint16_t initial counter value
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_start(value)             \
do {                                            \
    counter2_mode0_set_value(value);            \
                                                \
    bit_set(AUXR, SBIT4);                       \
} while (0);

/**
 * @brief Stop counter2
 * @details Stop count T0 pin state changes. 
 * Before stop counter2_start should be called.
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_stop()                   \
do {                                            \
    bit_clr(AUXR, CBIT4);                       \
} while (0)


/**
 * @brief Get counter2 mode0 started status.
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup counter2_mode0
 */
#define is_counter2_mode0_started() (test_if_bit_set(_AUXR, SBIT4))
///@}

/** @name read/write
 *  Counter2 get and set value functions 
 */
///@{

/**
 * @brief get counter2 value in mode0
 * 
 * @return uint16_t counter value
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_get_value() ((((uint16_t) T2H) << 8) | T2L)

/**
 * @brief set counter2 value in mode0
 * 
 * @details Call this method before counter2 started.
 * 
 * @param value uint16_t counter value to set
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_set_value(value)         \
do {                                            \
    static_assert(value <= 0xffff, "value to large"); \
    const uint16_t _val = (value);              \
    T2H = (uint8_t)(_val >> 8);                 \
    T2L = (uint8_t)(_val & 0xff);               \
} while(0)
///@}

/** @name config
 *  Counter2 pin output and gate config functions 
 */
///@{
/**
 * @brief enable output to P3.0
 * 
 * @details Enable pin P.3.0 state changes on counter2 overflow.
 * By default P3.0 output is disabled
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_enable_P30_output()   (bit_set(INT_CLKO, SBIT2))

/**
 * @brief disable output to P3.0
 * 
 * @details Disable pin P.3.0 state changes on counter2 overflow.
 * By default P3.0 output is disabled
 * 
 * @ingroup counter2_mode0
 */
#define counter2_mode0_disable_P30_output()   (bit_clr(INT_CLKO, CBIT2))

/**
 * @brief get pin P3.0 output state to P3.0
 * 
 * @returns true if P3.0 output enabled otherwise false
 * 
 * @ingroup counter2_mode0
 */
#define is_counter2_mode0_P30_output_enabled()   (test_if_bit_set(INT_CLKO, SBIT2))
///@}

#endif
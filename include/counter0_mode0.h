#ifndef STC15_COUNTER0_MODE0H
#define STC15_COUNTER0_MODE0H

/**
 * @file counter0_mode0.h
 * @defgroup counter0_mode0 Counter0 Mode0
 * @details Functions and data structures for counter0 mode0.
 * 
 * This module supports general purpose counter0.
 * Mode0 is auto reload 16-bit counter.
 * 
 * Counter0 increments its value on T0 pin change state  from 0 to 1. 
 * Once the counter reaches its maximum value of 65535, 
 * the counter is reset to zero at the next increment. 
 * On counter overflow reset interrupt 1 is raised.
 * 
 * @author Michael Golovanov
*/
#include <stdint.h>
#include <stdbool.h>

#include <interrupt.h>

/**
 * @brief T0 pin definition
 * 
 * @ingroup counter0_mode0
 */
#define T0 P34

/** @name init
 *  Counter initializaion functions 
 */
///@{
/**
 * @brief Initialize mode0 for counter0. 
 * 
 * @details Enable counter0 interrupt and set mode0
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_init()                   \
do {                                            \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
                                                \
    /* TMOD.3/GATE = 0; */                      \
    /* TMOD.2/(Timer or Counter mode) = 1; */   \
    /* TMOD.1/M1 timer0 = 0; */                 \
    /* TMOD.0/M0 timer0= 0; */                  \
    TMOD |= 0x04; /* init Counter0 */           \
} while(0)
///@}

/** @name run
 *  Counter run/stop/reload functions 
 */
///@{

/**
 * @brief Run counter0.
 * 
 * @details Before run counter0_mode0_init should be called.
 * After run counter0 is counted T0 pin state change.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * @param value uint16_t initial counter value
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_start(value)             \
do {                                            \
    counter0_mode0_set_value(value);            \
                                                \
    TF0 = 0;                                    \
    TR0 = 1;                                    \
} while (0);

/**
 * @brief Stop counter0
 * @details Stop count T0 pin state changes. 
 * Before stop counter0_start should be called.
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_stop()                   \
do {                                            \
    TR0 = 0;                                    \
} while (0)


/**
 * @brief Get counter0 mode0 started status.
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup counter0_mode0
 */
#define is_counter0_mode0_started() (TR0 == 1 && (is_counter0_mode0_gate_opened() || INT0 == 1) )
///@}

/** @name read/write
 *  Counter get and set value functions 
 */
///@{

/**
 * @brief get counter0 value in mode0
 * 
 * @return uint16_t counter value
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_get_value() ((((uint16_t) TH0) << 8) | TL0)

/**
 * @brief set counter0 value in mode0
 * 
 * @details Call this method before counter0 started.
 * 
 * @param value uint16_t counter value to set
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_set_value(value)         \
do {                                            \
    TH0 = (uint8_t)(value >> 8);                \
    TL0 = (uint8_t)(value & 0xff);              \
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
#define counter0_mode0_enable_P35_output()   (bit_set(INT_CLKO, SBIT0))

/**
 * @brief disable output to P3.5
 * 
 * @details Disable pin P.3.5 state changes on counter0 overflow.
 * By default P3.5 output is disabled
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_disable_P35_output()   (bit_clr(INT_CLKO, CBIT0))

/**
 * @brief get pin P3.5 output state to P3.5
 * 
 * @returns true if P3.5 output enabled otherwise false
 * 
 * @ingroup counter0_mode0
 */
#define is_counter0_mode0_P35_output_enabled()   (test_if_bit_set(INT_CLKO, SBIT0))

/**
 * @brief Open counter0 gate.
 * 
 * @details When gate is opened counter0 will count.
 * By default after init gate is opened. 
 * This routine explicitly open the gate.  
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_open_gate() (bit_clr(TMOD, CBIT3))

/**
 * @brief Close counter0 gate.
 * 
 * @details Closing gate stop counter0.
 * 
 * @ingroup counter0_mode0
 */
#define counter0_mode0_close_gate() (bit_set(TMOD, SBIT3))

/**
 * @brief Get gate state
 * 
 * @details returns bool. True if gate is opened and false if gate is closed  
 * 
 * @ingroup counter0_mode0
 */
#define is_counter0_mode0_gate_opened() (test_if_bit_cleared(TMOD, SBIT3))
///@}

#endif
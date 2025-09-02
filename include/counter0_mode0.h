#ifndef STC15_COUNTER0_MODE0H
#define STC15_COUNTER0_MODE0H

/**
 * @file counter0_mode0.h
 * @defgroup counter0_mode0 Counter0 Mode0
 * @details Functions and data structures for counter0 mode0.
 * 
 * This module supports general purpose counter0.
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
void counter0_mode0_stop();

/**
 * @brief Get counter0 mode0 started status.
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup counter0_mode0
 */
bool is_counter0_mode0_started();
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
uint16_t counter0_mode0_get_value();

/**
 * @brief set counter0 value in mode0
 * 
 * @details Call this method before counter0 started.
 * 
 * @param value uint16_t counter value to set
 * 
 * @ingroup counter0_mode0
 */
void counter0_mode0_set_value(uint16_t value);

///@}
#endif
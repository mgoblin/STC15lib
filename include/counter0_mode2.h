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

#endif

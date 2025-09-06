#ifndef STC15_COUNTER0_MODE1H
#define STC15_COUNTER0_MODE1H

/**
 * @file counter0_mode1.h
 * @defgroup counter0_mode1 Counter0 mode 1
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
 * 
 * @ingroup counter0_mode1
 */
#define counter0_mode1_init()                   \
do {                                            \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
                                                \
    TMOD = (TMOD & 0xF0) | 0x01;                \
} while(0)    

///@}

#endif

#ifndef STC15_TIMER0_MODE2H
#define STC15_TIMER0_MODE2H

/**
 * @file timer0_mode2.h
 * @defgroup timer0_mode2 Timer0 Mode2
 * @details Functions and data structures for timer0 mode2.
 * 
 * This module supports general purpose timer0.
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * For timer0 in mode2:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * Timer0 in mode2 can be used in sync (main prorgam flow blocked until timer overloaded) 
 * and interrupt (call interrupt handler on timer overloaded) modes.
 * 
 * CPU frequency change biased timer delays.
 *  
 * @author Michael Golovanov
 */

#include <sys.h>
#include <bits.h>
#include <interrupt.h>

#include <stdint.h>
#include <stdbool.h>

#include <timer_structs.h>

/** @name init
 *  Timer initializaion functions 
 */
///@{
/**
 * @brief Initialize mode2 12T for timer0.
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_12T_init()                         \
{                                                       \
    enable_mcu_interrupts();                            \
    enable_timer0_interrupt();                          \
    TMOD &= 0xf0;                                       \
    bit_set(TMOD, 1);                                   \
    bit_clr(AUXR, 7);                                   \
}

/**
 * @brief Initialize mode2 12T for timer0.
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_1T_init()                          \
{                                                       \
    enable_mcu_interrupts();                            \
    enable_timer0_interrupt();                          \
    TMOD &= 0xf0;                                       \
    bit_set(TMOD, 1);                                   \
    bit_set(AUXR, 7);                                   \
}
///@}

#endif

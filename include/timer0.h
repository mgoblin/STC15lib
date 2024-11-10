#ifndef STC15_TIMER0H
#define STC15_TIMER0H

/**
 * @file timer0.h
 * @defgroup timer0 Timer0
 * @details Functions and data structures for timer0.
 * 
 * This module supports general purpose timer0.
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * 8051 chips timer0 has 4 modes
 * * mode0 - 16-Bit Auto-Reload Timer/Counter
 * * mode1 - 16-Bit Timer/Counter
 * 
 * For timer:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * Timer0 can be used in sync (main prorgam flow blocked until timer overloaded) 
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

/**
 * Get timer0 mode
 * 
 * @return timer0 mode in range from 0 to 3
 * 
 * @ingroup timer0
 */
#define get_timer0_mode() (TMOD & 0x03)

/**
 * Get timer0 clock divider
 * 
 * @return timer0 clock divider
 * 
 * @ingroup timer0
 */
#define get_timer0_clock_divider() (get_bit(AUXR, 7) == 0 ? T12 : T1)

/**
 * Get output to pin P3.5 output flag enabled value
 * 
 * @return true if output enabled oterwise false
 * 
 * @ingroup timer0
 */
#define is_timer0_P35_output_enabled() (INT_CLKO & 0x01 > 0)

/**
 * @brief Disable timer on INT0(P3.2) pin is low
 * 
 * @details if you wand resore default timer behaviour indepned of INT0 state
 * reinit timer should be done 
 * 
 * @ingroup timer0
 */
# define timer0_enable_on_pinINT0_high() (bit_set(TMOD, 3))

/**
 * @brief Enable output of meandr with timer interval on P3.5 pin.
 * @details By default output is disabled
 * 
 * @param enable bool if true output is enabled otherwise output is disabled 
 * 
 * @ingroup timer0
 */
#define timer0_enableP35_output(enable) (enable ? bit_set(INT_CLKO, 0) : bit_clr(INT_CLKO, 0))

//============================== Timer0 mode0 declarations begin ==========================

/**
 * Initialize mode0 12T for timer0 in mode0. Set TMOD bits.
 * 
 * @ingroup timer0
 */
#define timer0_mode0_12T_init() {               \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
    TMOD &= 0xf0;                               \
    bit_clr(AUXR, 7);                           \
}

/**
 * @brief Initialize mode0 1T for timer0.
 * 
 * @ingroup timer0
 */
#define timer0_mode0_1T_init() {                \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
    TMOD &= 0xf0;                               \
    bit_set(AUXR, 7);                           \
}

//============================== Timer0 mode0 declarations end ============================

//============================== Timer0 mode1 declarations begin ==========================

/**
 * Initialize mode1 12T for timer0 in mode1. 
 * 
 * @ingroup timer0
 */
#define timer0_mode1_12T_init() {                       \
    enable_mcu_interrupts();                            \
    enable_timer0_interrupt();                          \
    TMOD &= 0xf0;                                       \
    TMOD |= 0x01;                                       \
    bit_clr(AUXR, 7);                                   \
}

/**
 * Initialize mode1 1T for timer0 in mode1. Set TMOD bits.
 * 
 * @ingroup timer0
 */
#define timer0_mode1_1T_init() {                        \
    enable_mcu_interrupts();                            \
    enable_timer0_interrupt();                          \
    TMOD &= 0xf0;                                       \
    TMOD |= 0x01;                                       \
    bit_set(AUXR, 7);                                   \
}

/**
 * @brief Run timer0 mode1 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode1_12T_init or timer0_mode1_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * 
 * Dont mix call of timer0_mode0_run_once_and_wait with
 * timer0_mode1_start/timer0_mode1_stop calls.
 * 
 * For mode0 and mode1 implementation is the same.
 * 
 * @param ticks uint16_t timer ticks count
 * 
 * @ingroup timer0 
 */
#define timer0_mode1_run_once_and_wait timer0_mode0_run_once_and_wait

//============================== Timer0 mode1 declarations end ============================

/**
 * @brief Run timer0 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode0_12T_init or timer0_mode0_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * 
 * Dont mix call of timer0_mode0_run_once_and_wait with
 * timer0_mode0_start/timer0_mode0_stop calls.
 * 
 * For mode0 and mode1 implementation is the same.
 * 
 * @param ticks uint16_t timer ticks count 
 * 
 * @ingroup timer0 
 */
#define timer0_mode0_run_once_and_wait(ticks) {                         \
    uint16_t value = 0xffff - ticks;                                    \
    /* Load timer high and low bytes value */                           \
    TL0 = value & 0xff;                                                 \
    TH0 = (value >> 8) & 0xff;                                          \
    TF0 = 0; /* clear timer overload flag */                            \
    TR0 = 1; /* set run timer flag */                                   \
    /* Waiting for timer overloaded (timer overload flag set to 1) */   \
    while(!TF0)                                                         \
    {                                                                   \
    }                                                                   \
    TR0 = 0; /* clear run timer flag */                                 \
    TF0 = 0; /* clear timer overload flag */                            \
}

/**
 * @brief Run timer0.
 * @details Before run timer0_modeX_12T_init or timer0_modeX_1T_init should be called.
 *  
 * After run program flow not blocked and interrupt will raised when timer is overloaded.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * Timer rerun after overloaded and interupt handler called. 
 * 
 * Dont mix call timer0_start call with 
 * void timer0_modeX_run_once_and_wait call
 * 
 * @param ticks uint16_t timer ticks count
 * 
 * @ingroup timer0
 */
#define timer0_start(ticks) {                               \
    uint16_t value = 0xffff - ticks;                        \
                                                            \
    /* Load timer high and low bytes value */               \
    TL0 = value & 0xff;                                     \
    TH0 = (value >> 8) & 0xff;                              \
                                                            \
    TF0 = 0; /* clear timer overload flag */                \
    TR0 = 1; /* set run timer flag */                       \
                                                            \
    /* Atfer method call finished interrupt handler */      \
    /* will be called on timer overload */                  \
    /* and timer will restore high and low bytes value */   \
    /* automatically */                                     \
} 

/**
 * @brief Stop timer0.
 * @details Before stop timer0_start should be called. 
 * Dont mix timer0_stop call with
 * timer0_modeX_run_once_and_wait call 
 * 
 * @ingroup timer0
 */
#define timer0_stop() {                                     \
    TR0 = 0; /* clear run timer flag */                     \
    TF0 = 0; /* clear timer overload flag */                \
}

#endif
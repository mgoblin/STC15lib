#ifndef STC15_TIMER0_MODE1H
#define STC15_TIMER0_MODE1H

/**
 * @file timer0_mode1.h
 * @defgroup timer0_mode1 Timer0 Mode1
 * @details Functions and data structures for timer0 mode1.
 * 
 * This module supports general purpose timer0.
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * Timer0 Mode1 is like mode0 but without timer reloading and P35 pin output features.
 * 
 * For timer0 in mode1:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * Timer0 in mode1 can be used in sync (main prorgam flow blocked until timer overloaded) 
 * and interrupt (call interrupt handler on timer overloaded) modes.
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
 * @brief Initialize mode1 12T for timer0. 
 * 
 * @ingroup timer0_mode1
 */
#define timer0_mode1_12T_init()                         \
{                                                       \
    enable_mcu_interrupts();                            \
    enable_timer0_interrupt();                          \
    TMOD &= 0xf0;                                       \
    bit_set(TMOD, 0);                                   \
    bit_clr(AUXR, 7);                                   \
}

/**
 * @brief Initialize mode1 1T for timer0. 
 * 
 * @ingroup timer0_mode1
 */
#define timer0_mode1_1T_init()                          \
{                                                       \
    enable_mcu_interrupts();                            \
    enable_timer0_interrupt();                          \
    TMOD &= 0xf0;                                       \
    bit_set(TMOD, 0);                                   \
    bit_set(AUXR, 7);                                   \
}
///@}

/** @name config
 *  Timer configuration functions 
 */
///@{
/** 
 * @brief Close timer starting gate.
 * @details When gate is closed timer will ticks after start only when INT0 pin is HIGH  
 * 
 * @ingroup timer0_mode1
*/
#define timer0_mode1_close_gate() (bit_set(TMOD, 3))

/** 
 * @brief Open timer starting gate.
 * @details When gate is open timer ticks after starts  
 * 
 * @ingroup timer0_mode1
*/
#define timer0_mode1_open_gate() (bit_clr(TMOD, 3))

/**
 * @brief Get timer starting gate state
 * 
 * @return bool true if gate is open otherwise false
 * 
 * @ingroup timer0_mode1
 */
#define is_timer0_mode1_gate_opened() (test_if_bit_cleared(TMOD, 3))

///@}

/** @name run in async mode
 *  Timer run/stop/reload functions 
 */
///@{
/**
 * @brief Run timer0.
 * @details Before run timer0_mode1_12T_init or timer0_mode1_1T_init should be called.
 *  
 * After run program flow not blocked and interrupt will raised when timer is overloaded.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * Timer rerun after overloaded and interupt handler called. 
 * 
 * Dont mix call timer0__mode1_start call with 
 * void timer0_mode1_delay call
 * 
 * @param ticks uint16_t timer ticks count. 
 * 
 * @ingroup timer0_mode1
 */
#define timer0_mode1_start(ticks)                           \
{                                                           \
    uint16_t value = 0xffff - ticks;                        \
    /* Load timer high and low bytes value */               \
    TL0 = value & 0xff;                                     \
    TH0 = (value >> 8) & 0xff;                              \
                                                            \
    TF0 = 0; /* clear timer overload flag */                \
    TR0 = 1; /* set run timer flag */                       \
} 

/**
 * @brief Stop timer0.
 * @details Before stop timer1_start should be called. 
 * Dont mix timer1_stop call with
 * timer0_mode1_delay call 
 * 
 * @ingroup timer0_mode1
 */
#define timer0_mode1_stop()                                 \
{                                                           \
    TR0 = 0; /* clear run timer flag */                     \
    TF0 = 0; /* clear timer overload flag */                \
}

/** 
 * @brief Get timer0 mode1 started status
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup timer0_mode1
 */
#define is_timer0_mode1_started() (TR0 == 1 && (is_timer0_mode1_gate_opened() || INT0 == 1))


///@}

/** @name run in sync mode
 *  Timer run once functions 
 */
///@{
/**
 * @brief Run timer0 mode1 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode1_12T_init or timer0_mode1_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * 
 * Dont mix call of timer0_mode1_delay with
 * timer0_mode1_open_gate/timer0_mode1_close_gate calls.
 * 
 * @param ticks uint16_t timer ticks count. 
 * 
 * @ingroup timer0_mode1
 */
#define timer0_mode1_delay(ticks)                                       \
{                                                                       \
    bool is_gate_opened = is_timer0_mode1_gate_opened();                \
                                                                        \
    timer0_mode1_open_gate();                                           \
                                                                        \
    timer0_mode1_start(ticks);                                          \
    /* Waiting for timer overloaded (timer overload flag set to 1) */   \
    while(!TF0)                                                         \
    {                                                                   \
    }                                                                   \
    timer0_mode1_stop();                                                \
                                                                        \
    if (!is_gate_opened)                                                \
    {                                                                   \
        timer0_mode1_close_gate();                                      \
    }                                                                   \
}
///@}

#endif

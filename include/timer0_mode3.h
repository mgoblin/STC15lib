#ifndef STC15_TIMER0_MODE3H
#define STC15_TIMER0_MODE3H

/**
 * @file timer0_mode3.h
 * @defgroup timer0_mode3 Timer0 Mode3
 * @details Functions and data structures for timer0 mode3.
 * 
 * This module supports general purpose timer0.
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * For timer0 in mode3:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1.
 * * Timer interrupt cannot be disabled 
 * 
 * Timer0 in mode3 can be used in sync (main prorgam flow blocked until timer overloaded) 
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

//============================== Timer0 mode3 declarations begin ==========================
/** @name init
 *  Timer initializaion functions 
 */
///@{
/**
 * @brief Initialize mode3 12T for timer0. 
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_12T_init()                 \
{                                               \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
    TMOD &= 0xf0;                               \
    TMOD |= 0x03;                               \
    bit_clr(AUXR, CBIT7);                       \
}

/**
 * @brief Initialize mode3 1T for timer0.
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_1T_init()                  \
{                                               \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
    TMOD &= 0xf0;                               \
    TMOD |= 0x03;                               \
    bit_set(AUXR, SBIT7);                       \
}
///@}
//============================== Timer0 mode3 declarations end ============================


/** @name config
 *  Timer configuration functions 
 */
///@{
/**
 * @brief Enable P35 meandr output
 * 
 * @param enable bool true if enabled and false if not
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_enable_P35_output(enable) (enable ? bit_set(INT_CLKO, SBIT0) : bit_clr(INT_CLKO, CBIT0))

/**
 * @brief Get output to pin P3.5 output flag enabled value
 * 
 * @return bool true if output enabled oterwise false
 * 
 * @ingroup timer0_mode3
 */
#define is_timer0_mode3_P35_output_enabled() (test_if_bit_set(INT_CLKO, SBIT0))

/** 
 * @brief Close timer starting gate.
 * @details When gate is closed timer will ticks after start only when INT0 pin is HIGH  
 * 
 * @ingroup timer0_mode3
*/
#define timer0_mode3_close_gate() (bit_set(TMOD, SBIT3))

/** 
 * @brief Open timer starting gate.
 * @details When gate is open timer ticks after starts  
 * 
 * @ingroup timer0_mode3
*/
#define timer0_mode3_open_gate() (bit_clr(TMOD, CBIT3))

/**
 * @brief Get timer starting gate state
 * 
 * @return bool true if gate is open otherwise false
 * 
 * @ingroup timer0_mode3
 */
#define is_timer0_mode3_gate_opened() (test_if_bit_cleared(TMOD, SBIT3))

///@}
//============================== Timer0 get mode, divider, pins declarations end =======


//============================== Timer0 run/stop declarations start =====================
/** @name run in async mode
 *  Timer run/stop/reload functions 
 */
///@{

/**
 * @brief Reload timer0 mode3 ticks on the fly
 * 
 * @details Reload is available in modes 0, 2, 3.
 * 
 * @param ticks uint16_t timer ticks reloaded value.
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_reload(ticks)                          \
{                                                           \
    uint16_t value = 0xffff - ticks;                        \
    /* Load timer high and low bytes value */               \
    TL0 = value & 0xff;                                     \
    TH0 = (value >> 8) & 0xff;                              \
}

/**
 * @brief Run timer0.
 * @details Before run timer0_mode3_12T_init or timer0_mode3_1T_init should be called.
 *  
 * After run program flow not blocked and interrupt will raised when timer is overloaded.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * Timer rerun after overloaded and interupt handler called. 
 * 
 * Dont mix call timer0_mode3_start call with 
 * void timer0_mode3_delay call
 * 
 * @param ticks uint16_t timer ticks count. 
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_start(ticks)                                                       \
{                                                                                       \
    timer0_mode3_reload(ticks);                                                         \
                                                                                        \
    TF0 = 0; /* clear timer overload flag */                                            \
    TR0 = 1; /* set run timer flag */                                                   \
} 

/**
 * @brief Stop timer0.
 * @details Before stop timer0_mode3_start should be called. 
 * Dont mix timer0_mode3_stop call with
 * timer0_mode3_delay call 
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_stop()                                 \
{                                                           \
    TR0 = 0; /* clear run timer flag */                     \
    TF0 = 0; /* clear timer overload flag */                \
}

/** 
 * @brief Get timer0 mode3 started status
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup timer0_mode3
 */
#define is_timer0_mode3_started() (TR0 == 1 && (is_timer0_mode3_gate_opened() || INT0 == 1))

///@}
//============================== Timer0 run/stop declarations end =======================

//============================== Timer0 run once declarations start =====================
/** @name run in sync mode
 *  Timer run once functions 
 */
///@{
/**
 * @brief Run timer0 mode3 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode3_12T_init or timer0_mode3_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * 
 * Dont mix call of timer0_mode3_delay with
 * timer0_mode3_open_gate/timer0_mode3_close_gate calls.
 * 
 * @param ticks uint16_t timer ticks count. 
 * 
 * @ingroup timer0_mode3
 */
#define timer0_mode3_delay(ticks)                                       \
{                                                                       \
    bool is_gate_opened = is_timer0_mode3_gate_opened();                \
                                                                        \
    timer0_mode3_open_gate();                                           \
                                                                        \
    timer0_mode3_start(ticks);                                          \
    /* Waiting for timer overloaded (timer overload flag set to 1) */   \
    while(!TF0)                                                         \
    {                                                                   \
    }                                                                   \
    timer0_mode3_stop();                                                \
                                                                        \
    if (!is_gate_opened)                                                \
    {                                                                   \
        timer0_mode3_close_gate();                                      \
    }                                                                   \
}
///@}
//============================== Timer0 run once declarations end =========================

#endif
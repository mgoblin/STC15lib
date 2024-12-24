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
 * Mode2 is 8-bit reloadable timer.
 * 
 * For timer0 in mode2:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * Timer0 in mode2 can be used in sync (main prorgam flow blocked until timer overloaded) 
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

/** 
 * @brief INT0 pin definition
 * 
 * @ingroup timer0_mode1
 */
#define INT0 P32

//============================== Timer0 mode2 declarations begin ==========================
/** @name init
 *  Timer initializaion functions 
 */
///@{
/**
 * @brief Initialize mode2 12T for timer0. 
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_12T_init()                 \
{                                               \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
    TMOD &= 0xf0;                               \
    TMOD |= 0x02;                               \
    bit_clr(AUXR, CBIT7);                       \
}

/**
 * @brief Initialize mode2 1T for timer0.
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_1T_init()                  \
{                                               \
    enable_mcu_interrupts();                    \
    enable_timer0_interrupt();                  \
    TMOD &= 0xf0;                               \
    TMOD |= 0x02;                               \
    bit_set(AUXR, SBIT7);                       \
}
///@}
//============================== Timer0 mode2 declarations end ============================


/** @name config
 *  Timer configuration functions 
 */
///@{
/**
 * @brief Enable P35 meander output
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_enable_P35_output() (bit_set(INT_CLKO, SBIT0))

/**
 * @brief Disable P35 meander output
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_disable_P35_output() (bit_clr(INT_CLKO, CBIT0))

/**
 * @brief Get output to pin P3.5 output flag enabled value
 * 
 * @return bool true if output enabled oterwise false
 * 
 * @ingroup timer0_mode2
 */
#define is_timer0_mode2_P35_output_enabled() (test_if_bit_set(INT_CLKO, SBIT0))

/** 
 * @brief Close timer starting gate.
 * @details When gate is closed timer will ticks after start only when INT0 pin is HIGH  
 * 
 * @ingroup timer0_mode2
*/
#define timer0_mode2_close_gate() (bit_set(TMOD, SBIT3))

/** 
 * @brief Open timer starting gate.
 * @details When gate is open timer ticks after starts  
 * 
 * @ingroup timer0_mode2
*/
#define timer0_mode2_open_gate() (bit_clr(TMOD, CBIT3))

/**
 * @brief Get timer starting gate state
 * 
 * @return bool true if gate is open otherwise false
 * 
 * @ingroup timer0_mode2
 */
#define is_timer0_mode2_gate_opened() (test_if_bit_cleared(TMOD, SBIT3))

///@}
//============================== Timer0 get mode, divider, pins declarations end =======


//============================== Timer0 run/stop declarations start =====================
/** @name run in async mode
 *  Timer run/stop/reload functions 
 */
///@{

/**
 * @brief Reload timer0 mode2 ticks on the fly
 * 
 * @details Reload is available in modes 0, 2, 3.
 * 
 * @param ticks uint8_t timer ticks reloaded value.
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_reload(ticks)                          \
{                                                           \
    /* Load timer value */                                  \
    TH0 = (0xff - ticks);                                   \
}

/**
 * @brief Reload timer0 mode2 TL0 on the fly
 * @details Reload is available in modes 0, 2, 3.
 * 
 * @param th0 uint8_t timer value
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_direct_reload(th0) (TH0 = th0)

/**
 * @brief Run timer0.
 * @details Before run timer0_mode2_12T_init or timer0_mode2_1T_init should be called.
 *  
 * After run program flow not blocked and interrupt will raised when timer is overloaded.
 * Interrupt handler void timer0ISR(void) __interrupt(1) should be defined in user code.
 * 
 * Timer rerun after overloaded and interupt handler called. 
 * 
 * Dont mix call timer0__mode2_start call with 
 * void timer0_mode2_delay call
 * 
 * @param ticks uint8_t timer ticks count. 
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_start(ticks)                                                       \
{                                                                                       \
    timer0_mode2_reload(ticks);                                                         \
                                                                                        \
    TF0 = 0; /* clear timer overload flag */                                            \
    TR0 = 1; /* set run timer flag */                                                   \
} 

/**
 * @brief Stop timer0.
 * @details Before stop timer2_start should be called. 
 * Dont mix timer0_mode2_stop call with
 * timer0_mode2_delay call 
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_stop()                                 \
{                                                           \
    TR0 = 0; /* clear run timer flag */                     \
    TF0 = 0; /* clear timer overload flag */                \
}

/** 
 * @brief Get timer0 mode2 started status
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup timer0_mode2
 */
#define is_timer0_mode2_started() (TR0 == 1 && (is_timer0_mode2_gate_opened() || INT0 == 1))

///@}
//============================== Timer0 run/stop declarations end =======================

//============================== Timer0 run once declarations start =====================
/** @name run in sync mode
 *  Timer run once functions 
 */
///@{
/**
 * @brief Run timer0 mode2 once and wait with program flow blocking timer not finished.
 * 
 * @details 
 * Before run timer0_mode2_12T_init or timer0_mode2_1T_init should be called. 
 * 
 * After run program flow blocked until timer does not overloaded.
 * 
 * Dont mix call of timer0_mode2_delay with
 * timer0_mode2_open_gate/timer0_mode2_close_gate calls.
 * 
 * @param ticks uint8_t timer ticks count. 
 * 
 * @ingroup timer0_mode2
 */
#define timer0_mode2_delay(ticks)                                       \
{                                                                       \
    timer0_mode2_start(ticks);                                          \
    /* Waiting for timer overloaded (timer overload flag set to 1) */   \
    while(!TF0)                                                         \
    {                                                                   \
    }                                                                   \
    timer0_mode2_stop();                                                \
}
///@}
//============================== Timer0 run once declarations end =========================

#endif
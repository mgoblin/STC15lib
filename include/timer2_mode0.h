#ifndef STC15_TIMER2_MODE0H
#define STC15_TIMER2_MODE0H

/**
 * @file timer2_mode0.h
 * @defgroup timer2_mode0 Timer2 Mode0
 * @details Functions and data structures for timer2 mode0.
 * 
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * 8051 chips timer2
 * * mode0 - 16-Bit Auto-Reload Timer/Counter
 * 
 * For timer:
 * * Input of timer is system clock.
 * * By default timer input is 12T mode. Timer increments by sysClock/12.
 * * Timer input can be switched to 1T mode. In this mode timer increments by sysClock/1. 
 * 
 * Timer2 mode0 can be used in sync (main prorgam flow blocked until timer overloaded) 
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
 * @brief Initialize mode0 12T for timer2. 
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/12.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_12T_init()                                         \
do {                                                                    \
    enable_mcu_interrupts();                                            \
    enable_timer2_interrupt();                                          \
    AUXR &= 0xE2;                                                       \
} while(0)

/**
 * @brief Initialize mode0 1T for timer2. 
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/1.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_1T_init()                                          \
do {                                                                    \
    enable_mcu_interrupts();                                            \
    enable_timer2_interrupt();                                          \
    AUXR &= 0xE2;                                                       \
    AUXR |= 0x05;                                                       \
} while(0)  
///@}

/** @name config
 *  Timer configuration functions 
 */
///@{

/**
 * @brief Enable output of meander with timer times on P3.0 pin.
 * @details By default output is disabled
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_enable_P30_output() (bit_set(INT_CLKO, SBIT2))

/**
 * @brief Disable output of meander with timer times on P3.0 pin.
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_disable_P30_output() (bit_clr(INT_CLKO, CBIT2))

/**
 * Get output to pin P3.0 output flag enabled value
 * 
 * @return bool true if output enabled oterwise false
 * 
 * @ingroup timer2_mode0
 */
#define is_timer2_mode0_P30_output_enabled() (test_if_bit_set(INT_CLKO, SBIT2))

///@}

/** @name run in async mode
 *  Timer run/stop/reload functions 
 */
///@{

/**
 * @brief Run timer2 mode0 with interrupt support.
 * 
 * @details 
 * Before run timer2_mode0_12T_init or timer2_mode0_1T_init should be called.
 *  
 * After run program flow not blocked and interrupt will raised when timer is overloaded.
 * 
 * Interrupt handler void timer2ISR(void) __interrupt(12) should be defined in user code.
 * 
 * Timer rerun occurs after overloading and interuppt handler calling. 
 * 
 * @param ticks uint16_t timer tick count
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_start(ticks)                           \
do {                                                        \
    timer2_mode0_reload(ticks);                             \
                                                            \
    bit_set(AUXR, SBIT4);                                   \
} while(0)

/**
 * @brief Run timer2 mode0 with direct set of TH0 and TL0 registers.
 * @details 
 * Before run timer2_mode0_12T_init or timer2_mode0_1T_init should be called.
 * 
 * After run program flow not blocked and interrupt will raised when timer is overloaded.
 * Interrupt handler void timer2ISR(void) __interrupt(12) should be defined in user code.
 * 
 * Timer rerun occurs after overloading and interuppt handler calling. 
 * Timer overloading occurs when [TH0, TL0] = 0xff + 1
 * 
 * @param th0 uint8_t TH0 value
 * @param tl0 uint8_t TL0 value
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_direct_start(th0, tl0)                 \
do {                                                        \
    timer2_mode0_direct_reload(th0, tl0);                   \
                                                            \
    bit_set(AUXR, SBIT4);                                   \
} while(0)

/**
 * @brief Stop timer2 mode0.
 * @details Before stop timer2_mode0_start should be called. 
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_stop() {                               \
    bit_clr(AUXR, CBIT4); /* clear T2 run flag */           \
}

/** 
 * @brief Get timer2 started status
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup timer2
 */
#define is_timer2_mode0_started() (test_if_bit_set(AUXR, SBIT4))

/**
 * @brief Reload timer2 ticks on the fly
 * 
 * @details Reload is available in mode 0 only
 * 
 * @param ticks uint16_t timer ticks reloaded value
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_reload(ticks)                              \
do {                                                            \
    uint16_t value = 0xffff - ticks;                            \
    T2L = value & 0xff;                                         \
    T2H = (value >> 8) & 0xff;                                  \
} while(0)

/**
 * @brief Reload timer2 T2H and T2L registers on the fly
 * @details Reload is available in mode 0 only
 * 
 * @param th2 uint8_t T2H value
 * @param tl2 uint8_t T2L value
 * 
 * @ingroup timer2_mode0
 */
#define timer2_mode0_direct_reload(th2, tl2)                    \
do {                                                            \
    T2H = th2;                                                  \
    T2L = tl2;                                                  \
} while(0)

///@}

#endif
#ifndef STC15_TIMER2H
#define STC15_TIMER2H

/**
 * @file timer2.h
 * @defgroup timer2 Timer2
 * @details Functions and data structures for timer2.
 * 
 * This module supports general purpose timer2.
 * Timer can work as COUNTER or TIMER. 
 * 
 * Counter increments on external singnal (like pin 1/0 change state). 
 * 
 * 8051 chips timer2 has 2 modes
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
 * Get timer2 mode
 * 
 * @return timer2 mode. Timer2 have only mode0.
 * 
 * @ingroup timer2
 */
#define get_timer2_mode() (0)

/**
 * Get timer2 clock divider
 * 
 * @return timer2 clock divider
 * 
 * @ingroup timer2
 */
#define get_timer2_clock_divider() (get_bit(AUXR, 2) == 0 ? T12 : T1)

/**
 * Get output to pin P3.0 output flag enabled value
 * 
 * @return bool true if output enabled oterwise false
 * 
 * @ingroup timer2
 */
#define is_timer2_P30_output_enabled() (get_bit(INT_CLKO, 2) > 0)

//============================== Timer2 mode0 declarations begin ==========================
/**
 * @brief Initialize mode0 12T for timer2. 
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/12.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer2
 */
#define timer2_mode0_12T_init() {                                       \
    enable_mcu_interrupts();                                            \
    enable_timer2_interrupt();                                          \
    /* bit_clr(AUXR, 4); clear T2 run flag */                           \
    /* bit_clr(AUXR, 3); // clear T/C flag for set timer mode */        \
    /* bit_clr(AUXR, 2); // clear T2 T2x12 flag for set 12T mode */     \
    AUXR &= 0xE3; /* 0b11100011 */                                      \
                                                                        \
}

/**
 * @brief Initialize mode0 1T for timer2. Set AUXR bits.
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/1.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer2
 */
#define timer2_mode0_1T_init() {                                        \
    enable_mcu_interrupts();                                            \
    enable_timer2_interrupt();                                          \
    /* bit_clr(AUXR, 4); // clear T2 run flag */                        \
    /*bit_clr(AUXR, 3); // clear T/C flag for set timer mode */         \
    /*bit_set(AUXR, 2); // set T2 T2x12 flag for set 1T mode */         \
    AUXR &= 0xE7;/*0b11100111;*/                                        \
}

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
 * @param tick uint16_t timer tick count
 * 
 * @ingroup timer2
 */
#define timer2_mode0_start(tick) {                          \
    uint16_t value = 0xffff - tick;                         \
    /* Load high and low timer value bytes */               \
    T2L = value & 0xff;                                     \
    T2H = (value >> 8) & 0xff;                              \
                                                            \
    bit_set(AUXR, 4); /* set T2 run flag */                 \
} 

/**
 * @brief Stop timer2 mode0.
 * @details Before stop timer2_mode0_start should be called. 
 * 
 * @ingroup timer2
 */
#define timer2_mode0_stop() {                               \
    bit_clr(AUXR, 4); /* clear T2 run flag */               \
}

/** 
 * @brief Get timer2 started status
 * 
 * @return bool true if started otherwise false
 * 
 * @ingroup timer2
 */
#define is_timer2_started() (test_if_bit_set(AUXR, 4))

/**
 * @brief Reload timer2 ticks on the fly
 * 
 * @details Reload is available in mode 0 only
 * 
 * @param ticks uint16_t timer ticks reloaded value
 * 
 * @ingroup timer2
 */
#define timer2_reload(ticks) {                                  \
    uint16_t value = 0xffff - ticks;                            \
    /* Load timer high and low bytes value */                   \
    T2L = value & 0xff;                                         \
    T2H = (value >> 8) & 0xff;                                  \
}

/**
 * @brief Enable output of meandr with timer times on P3.0 pin.
 * @details By default output is disabled
 * 
 * @param enable bool if true output is enabled otherwise output is disabled 
 * 
 * @ingroup timer2
 */
#define timer2_mode0_enableP30_output(enable) (enable ? bit_set(INT_CLKO, 2) : bit_clr(INT_CLKO, 2))

//============================== Timer2 mode0 declarations end ============================

#endif
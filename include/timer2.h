#ifndef STC15_TIMER2H
#define STC15_TIMER2H

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
 * @ingroup timer
 */
#define get_timer2_mode() (0)

/**
 * Get timer2 clock divider
 * 
 * @return timer2 clock divider
 * 
 * @ingroup timer
 */
#define get_timer2_clock_divider() (get_bit(AUXR, 2) == 0 ? T12 : T1)

/**
 * Get output to pin P3.0 output flag enabled value
 * 
 * @return true if output enabled oterwise false
 * 
 * @ingroup timer
 */
#define is_timer2_P30_output_enabled() (get_bit(INT_CLKO, 2) > 0)

//============================== Timer2 mode0 declarations begin ==========================
/**
 * @brief Initialize mode0 12T for timer2. Set AUXR bits.
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/12.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer
 */
#define timer2_mode0_12T_init() {                                       \
    enable_mcu_interrupts();                                            \
    /* bit_clr(AUXR, 4); clear T2 run flag */                           \
    /* bit_clr(AUXR, 3); // clear T/C flag for set timer mode */        \
    /* bit_clr(AUXR, 2); // clear T2 T2x12 flag for set 12T mode */     \
    AUXR &= 0xE3; /* 0b11100011 */                                      \
                                                                        \
    enable_timer2_interrupt();                                          \
}

/**
 * @brief Initialize mode0 1T for timer2. Set AUXR bits.
 * @details Timer2 could be used for UART. 
 * This method init timer2 as general purpose timer in mode0 with input from sysClk/1.
 * Using timer2 in this mode disable UART capability.
 * 
 * @ingroup timer
 */
#define timer2_mode0_1T_init() {                                        \
    enable_mcu_interrupts();                                            \
    /* bit_clr(AUXR, 4); // clear T2 run flag */                        \
    /*bit_clr(AUXR, 3); // clear T/C flag for set timer mode */         \
    /*bit_set(AUXR, 2); // set T2 T2x12 flag for set 1T mode */         \
    AUXR &= 0xE7;/*0b11100111;*/                                        \
                                                                        \
    enable_timer2_interrupt();                                          \
}

/**
 * @brief Run timer2 mode0 with interrupt support.
 * @details Before run timer2_mode0_12T_init or timer2_mode0_1T_init should be called. 
 * After run program flow not blocked and interrupt will generated when timer is overloaded.
 * Interrupt handler void timer2ISR(void) __interrupt(12) should be defined in user code.
 * Timer rerun after overloaded and interuppt handler called. 
 * 
 * @param th_value timer interval prescaler (high 8 bits)
 * @param tl_value timer interval prescaler (low 5 bits)
 * 
 * @ingroup timer
 */
void timer2_mode0_start(uint8_t th_value, uint8_t tl_value);

/**
 * @brief Stop timer2 mode0 with interrupt support.
 * @details Before stop timer2_mode0_start should be called. 
 * 
 * @ingroup timer
 */
void timer2_mode0_stop();

/**
 * @brief Enable output of meandr with timer times on P3.0 pin.
 * @details By default output is disabled
 * 
 * @param enable bool if true output is enabled otherwise output is disabled 
 * 
 * @ingroup timer
 */
#define timer2_mode0_enableP30_output(enable) (enable ? bit_set(INT_CLKO, 2) : bit_clr(INT_CLKO, 2))

//============================== Timer2 mode0 declarations end ============================

#endif
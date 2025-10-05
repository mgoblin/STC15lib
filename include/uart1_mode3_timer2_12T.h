#ifndef STC15_UART1MODE3_T212H
#define STC15_UART1MODE3_T212H

#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <frequency.h>
#include <interrupt.h>
#include <uart1_shared.h>

typedef enum 
{
    /** @brief 1200 baudrate */
    baudrate_1200 = 0xFF3F,
    /** @brief 2400 baudrate */
    baudrate_2400 = 0xFF9F,
    /** @brief 4800 baudrate */
    baudrate_4800 = 0xFFCF,
    /** @brief 9600 baudrate */
    baudrate_9600 = 0xFFE7,
} uart1_mode3_timer2_12t_baudrate_t;

#define uart1_mode3_timer2_12T_init(pins)                       \
do {                                                            \
    enable_mcu_interrupts();                                    \
    enable_uart1_interrupt();                                   \
    disable_timer2_interrupt();                                 \
                                                                \
    PCON &= 0x3F;                                               \
    SCON = 0xD0;                                                \
                                                                \
    /* The clock source of Timer 2 is SYSclk/12. AUXR.T2x12 = 0 */ \
    /* AUXR.UART_M0x6 = 0 */                                    \
    /* Timer2 is not started. AUXR.T2R = 0 */                   \
    /* Timer2 are used as timer. AUXR.T2_C/T = 0 */             \
    AUXR &= 0xC2;                                               \
                                                                \
    /* Select Timer2 as UART1 baud rate generator. AUXR.S1ST2 = 1; */ \
    bit_set(AUXR, SBIT0);                                       \
                                                                \
    /* Point-to-point mode */                                   \
    bit_clr(CLK_DIV, CBIT4);                                    \
                                                                \
    /* Set AUXR1 bits 6, 7 to select RxD/TxD pins */            \
    AUXR1 &= 0x3F;                                              \
    AUXR1 |= pins;                                              \
} while (0)    


#define uart1_mode3_timer2_12T_start(baudrate)                  \
do {                                                            \
    /* Set TH TL values */                                      \
    T2L = baudrate & 0xFF;                                      \
    T2H = baudrate >> 8;                                        \
                                                                \
    /* Start Timer2 */                                          \
    bit_set(AUXR, SBIT4);                                       \
} while (0)

#define uart1_mode3_timer2_12T_ticks(baudrate) (65536 - ((((MAIN_Fosc / 12) / baudrate) >> 2) >> get_frequency_divider_scale()))

#define uart1_mode3_timer2_12T_start_ext(baudrate)              \
do {                                                            \
    const uint16_t ticks = uart1_mode1_timer2_12T_ticks(baudrate);\
                                                                \
    /* Set TH TL values */                                      \
    T2L = ticks & 0xFF;                                         \
    T2H = ticks >> 8;                                           \
                                                                \
    /* Start Timer2 */                                          \
    bit_set(AUXR, SBIT4);                                       \
} while (0)


#define uart1_mode3_timer2_12T_stop (bit_clr(AUXR, CBIT4))

#define is_uart1_mode3_timer2_12T_started() (test_if_bit_set(AUXR, SBIT4))

#endif
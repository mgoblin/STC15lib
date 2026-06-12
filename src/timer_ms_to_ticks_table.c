/**
 * @file timer_ms_to_ticks_table.c
 * @brief Implementation of timer to milliseconds conversion using lookup tables
 * 
 * This file provides the implementation for fast millisecond to tick conversion
 * using precalculated lookup tables. The tables contain precomputed values for
 * 1 millisecond delays at various system clock frequencies and divider settings.
 * 
 * Lookup table organization:
 * - precalc_1t_ticks: Values for 1T mode (1 clock cycle per tick)
 * - precalc_12t_ticks: Values for 12T mode (12 clock cycles per tick)
 * 
 * Each array has 8 elements, with the index corresponding to the frequency scale
 * divider (from CLK_DIV register bits [0..2]). The frequency scale ranges from
 * 0 to 7, corresponding to clock dividers of 1, 2, 4, 8, 16, 32, 64, and 128.
 * 
 * The precalculated values are derived from the formula:
 * ticks = (SYSclk / divider) * 0.001
 * 
 * Where SYSclk = MAIN_Fosc / (2^divider_scale)
 * 
 * Example calculations for 11,059,200 Hz crystal:
 * - 1T mode, divider_scale=0 (SYSclk=11,059,200 Hz): ticks = 11059
 * - 12T mode, divider_scale=0 (SYSclk=11,059,200 Hz): ticks = 922
 * 
 * @note The values in the tables are rounded approximations. The actual
 *       values in comments show the exact mathematical results.
 * 
 * @note The timer_ms_to_ticks_table.h header provides the public API for
 *       accessing these lookup tables via the timer_1ms_to_ticks() function.
 * 
 * @see timer_ms_to_ticks_table.h - Public API for table-based conversion
 * @see timer_to_ms_common.h - Dynamic conversion functions
 * @see frequency.h - System clock frequency management
 * 
 * @author Michael Golovanov
*/

#include <timer_ms_to_ticks_table.h>
#include <frequency.h>
#include <interrupt.h>

/**
 * @brief Precalculated timer ticks for 1ms delay in 1T mode
 * @details Array index corresponds to frequency scale divider (CLK_DIV bits [0..2])
 * 
 * These values represent the number of timer ticks required for a 1 millisecond
 * delay when the timer is configured in 1T mode (one clock cycle per tick).
 * The array index is determined by the system clock frequency scale setting.
 * 
 * Index mapping:
 * - Index 0: divider_scale=0, SYSclk = MAIN_Fosc, divider=1
 * - Index 1: divider_scale=1, SYSclk = MAIN_Fosc/2, divider=2
 * - Index 2: divider_scale=2, SYSclk = MAIN_Fosc/4, divider=4
 * - Index 3: divider_scale=3, SYSclk = MAIN_Fosc/8, divider=8
 * - Index 4: divider_scale=4, SYSclk = MAIN_Fosc/16, divider=16
 * - Index 5: divider_scale=5, SYSclk = MAIN_Fosc/32, divider=32
 * - Index 6: divider_scale=6, SYSclk = MAIN_Fosc/64, divider=64
 * - Index 7: divider_scale=7, SYSclk = MAIN_Fosc/128, divider=128
 * 
 * @note Values in comments show exact mathematical calculations
 * 
 * @see get_frequency_divider_scale() - Function to get current index
 * @see timer_1ms_to_ticks() - Function using this table
 */
uint16_t precalc_1t_ticks[8] = 
{
    11070,  // 0 11059 
    5510,   // 1 5548
    2733,   // 2 2774
    1343,   // 3 1387
    650,    // 4 693
    300,    // 5 347
    127,    // 6 173
    43,     // 7 87
};

/**
 * @brief Precalculated timer ticks for 1ms delay in 12T mode
 * @details Array index corresponds to frequency scale divider (CLK_DIV bits [0..2])
 * 
 * These values represent the number of timer ticks required for a 1 millisecond
 * delay when the timer is configured in 12T mode (twelve clock cycles per tick).
 * The array index is determined by the system clock frequency scale setting.
 * 
 * Index mapping:
 * - Index 0: divider_scale=0, SYSclk = MAIN_Fosc, divider=12
 * - Index 1: divider_scale=1, SYSclk = MAIN_Fosc/2, divider=24
 * - Index 2: divider_scale=2, SYSclk = MAIN_Fosc/4, divider=48
 * - Index 3: divider_scale=3, SYSclk = MAIN_Fosc/8, divider=96
 * - Index 4: divider_scale=4, SYSclk = MAIN_Fosc/16, divider=192
 * - Index 5: divider_scale=5, SYSclk = MAIN_Fosc/32, divider=384
 * - Index 6: divider_scale=6, SYSclk = MAIN_Fosc/64, divider=768
 * - Index 7: divider_scale=7, SYSclk = MAIN_Fosc/128, divider=1536
 * 
 * @note Values in comments show exact mathematical calculations
 * 
 * @see get_frequency_divider_scale() - Function to get current index
 * @see timer_1ms_to_ticks() - Function using this table
 */
uint16_t precalc_12t_ticks[8] = 
{
    922,    // 0 925
    459,    // 1 462
    227,    // 2 231
    112,    // 3 116
    54,     // 4 58
    25,     // 5 29
    10,     // 6 14
    4,      // 7 7
}; 

void timer0_1ms_delay_init()
{
    disable_timer0_interrupt();
    uint8_t scale = get_frequency_divider_scale();
    timer_clock_divider_t divider = get_timer0_clock_divider();
    ticks  = divider == T1 ? 
        precalc_1t_ticks[scale] :
        precalc_12t_ticks[scale];
    uint16_t value = 0xffff - ticks;    
    TH0 = value >> 8; 
    TL0 = value & 0xff;
}

// Call timer0_1ms_delay_init before
void timer0_1ms_delay()
{
    TF0 = 0;
    TR0 = 1;
    while(!TF0);
    TR0 = 0;
}

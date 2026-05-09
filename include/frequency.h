#ifndef STC15_FREQH
#define STC15_FREQH

/**
 * @file frequency.h
 * @defgroup freq Frequency
 * @details Functions and data structures for get chip CPU frequency.
 * Chip CPU frequency defined in sys.h as a MAIN_Fosc constant. 
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <sys.h>
#include <bits.h>

/** 
 * @brief MCU frequency divider bitmask (3 low bits of CLK_DIV registry)
 * 
 * @ingroup freq 
 */
#define CLK_DIV_MASK 0x07

/**
 * @brief Get MAIN_Fosc value
 * 
 * @return MAIN_Fosc value
 * 
 * @ingroup freq
 * 
 */
#define get_master_clock_frequency() (MAIN_Fosc)

/**
 * @brief Get high part of MAIN_Fosc defined as MAIN_FoscH in sys.h
 * 
 * @return MAIN_FoscH
 * 
 * @ingroup freq
 */
#define get_master_clock_frequency_high_part() (MAIN_FoscH)

/**
 * @brief Get low part of MAIN_Fosc defined as MAIN_FoscL in sys.h
 * 
 * @return MAIN_FoscL
 * 
 * @ingroup freq
 */
#define get_master_clock_frequency_low_part() (MAIN_FoscL)

/**
 * @brief Get master clock frequency divider (1 << CLK_DIV bits [0..2])
 * 
 * @return master clock frequency divider. Divider values range is from 1 to 128.
 * 
 * @see get_frequency_divider_scale(uint8_t divider_scale)
 * 
 * @ingroup freq
 */
#define get_frequency_divider() (1 << get_frequency_divider_scale())

/**
 * @brief Get master clock frequency divider scale (CLK_DIV bits [0..2])
 * 
 * @return master clock frequency divider scale. Divider scale range is from 0 to 7.
 * 
 * @see get_frequency_divider_scale(uint8_t divider_scale)
 * 
 * @ingroup freq
 */
#define get_frequency_divider_scale() (CLK_DIV & CLK_DIV_MASK)

/**
 * @brief Update and get master clock frequency divider (CLK_DIV bits [0..2])
 * @details Before setting divider value validate if divider scale is out of range 0..7. 
 * 
 * @param divider_scale uint8 scale from 0 to 7 corresponds dividers 1, 2, 4, ...128 
 * 
 * @return master clock frequency divider value
 * 
 * @see get_frequency_divider()
 * 
 * @ingroup freq
 */
#define set_frequency_divider_scale(divider_scale)      \
do {                                                    \
    CLK_DIV &= 0xf8;                                    \
    CLK_DIV |= (divider_scale & CLK_DIV_MASK);          \
} while(0)


/**
 * @brief System clock frequency
 * 
 * This routine calculates the actual system clock frequency that the CPU is running at,
 * taking into account the main oscillator frequency and the clock divider setting.
 * 
 * The formula is: SYSclk = MAIN_Fosc / (2^divider_scale)
 * where:
 * - MAIN_Fosc is the main oscillator frequency defined in sys.h
 * - divider_scale is the value in bits [0..2] of the CLK_DIV register
 * 
 * This represents the effective CPU clock frequency after any prescaling has been applied.
 * For example, if MAIN_Fosc is 11,059,200 Hz and the divider_scale is 1 (dividing by 2),
 * then SYSclk would be 5,529,600 Hz.
 * 
 * @see get_master_clock_frequency() - function that returns the main oscillator frequency
 * @see get_frequency_divider_scale() - function that returns the current clock divider scale
 * @see set_frequency_divider_scale() - function to change the clock divider
 * 
 * @ingroup freq
 */
#define SYSclk (get_master_clock_frequency() >> get_frequency_divider_scale())

/**
 * @brief Enable master clock output. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)  
 * 
 * @ingroup freq
 */
#define enable_master_clock_output_div1() (CLK_DIV |= 0x40)

/**
 * @brief Enable (master clock output)/2. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
#define enable_master_clock_output_div2() (CLK_DIV |= 0x80)

/**
 * @brief Enable (master clock output)/4. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
#define enable_master_clock_output_div4() (CLK_DIV |= 0xC0)

/**
 * @brief Disable master clock output
 * 
 * @see enable_master_clock_output_div1() 
 * @see enable_master_clock_output_div2()
 * @see enable_master_clock_output_div4()  
 * 
 * @ingroup freq
 */
#define disable_master_clock_output() (CLK_DIV &= 0x3f)

/**
 * @brief Master clock output pins enumeration
 * 
 * @ingroup freq
 */
typedef enum 
{
    /// output disabled
    NONE, 
    /// output to pin 5.4
    P5_4, 
    /// output to pin 1.6
    P1_6  
} master_clock_output_pin_t;

/**
 * @brief Get master clock output
 * 
 * @return info about current master clock output
 * 
 * @ingroup freq
 */
#define get_master_clock_output_pin() ((CLK_DIV & 0xC0) == 0 ? NONE : (CLK_DIV & 0x08) == 0 ? P5_4 : P1_6)

/**
 * @brief Set master clock output pin
 * 
 * @param pin master_clock_output_pin_t pin to set output
 * 
 * @ingroup freq
 */
#pragma save
#pragma disable_warning 126
#define set_master_clock_output_pin(pin)            \
do {                                                \
    if (pin == NONE)                                \
    {                                               \
        disable_master_clock_output();              \
    }                                               \
    else if (pin == P5_4)                           \
    {                                               \
        bit_clr(CLK_DIV, CBIT3);                    \
    }                                               \
    else if (pin == P1_6)                           \
    {                                               \
        bit_set(CLK_DIV, SBIT3);                    \
    }                                               \
} while(0)
#pragma restore

#endif 
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
#define get_frequency_divider() (1 << (CLK_DIV & 0x07))

/**
 * @brief Get master clock frequency divider scale (CLK_DIV bits [0..2])
 * 
 * @return master clock frequency divider scale. Divider scale range is from 0 to 7.
 * 
 * @see get_frequency_divider_scale(uint8_t divider_scale)
 * 
 * @ingroup freq
 */
#define get_frequency_divider_scale() (CLK_DIV & 0x07)

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
    CLK_DIV |= (divider_scale & 0x07);                  \
} while(0)

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
#ifndef STC15_FREQH
#define STC15_FREQH

/**
 * @file frequency.h
 * @defgroup freq Frequency
 * @details Functions and data structures for get chip CPU frequency.
 * Chip CPU frequency defined in sys.h as a MAIN_Fosc constant. 
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <sys.h>

/**
 * Get MAIN_Fosc value
 * 
 * @return MAIN_Fosc value
 * 
 * @ingroup freq
 */
#define get_master_clock_frequency() (MAIN_Fosc)

/**
 * Get high part of MAIN_Fosc defined as MAIN_FoscH in sys.h
 * 
 * @return MAIN_FoscH
 * 
 * @ingroup freq
 */
#define get_master_clock_frequency_high_part() (MAIN_FoscH)

/**
 * Get low part of MAIN_Fosc defined as MAIN_FoscL in sys.h
 * 
 * @return MAIN_FoscL
 * 
 * @ingroup freq
 */
#define get_master_clock_frequency_low_part() (MAIN_FoscL)

/**
 * Get master clock frequency divider (CLK_DIV bits [0..2])
 * 
 * @return master clock frequency divider. Divider values range is from 1 to 128.
 * 
 * @see update_and_get_frequency_divider(uint8_t divider_scale)
 * 
 * @ingroup freq
 */
#define get_frequency_divider() (1 << (CLK_DIV & 0x07))

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
#define update_and_get_frequency_divider(divider_scale) { \
    if (divider_scale < 8) \
    { \
        CLK_DIV &= (0xf8 | divider_scale); \
    } \
    get_frequency_divider(); \
}

/**
 * Enable master clock output. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
#define enable_master_clock_output_div1() (CLK_DIV |= 0x40)

/**
 * Enable (master clock output)/2. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
#define enable_master_clock_output_div2() (CLK_DIV |= 0x80)

/**
 * Enable (master clock output)/4. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
#define enable_master_clock_output_div4() (CLK_DIV |= 0xC0)

/**
 * Disable master clock output
 * 
 * @ingroup freq
 */
#define disable_master_clock_output() (CLK_DIV &= 0x3f)

/**
 * Master clock output pins enumeration
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
 * Get master clock output
 * 
 * @return info about current master clock output
 * 
 * @ingroup freq
 */
master_clock_output_pin_t get_master_clock_output_pin();

/**
 * Set master clock output pin
 * 
 * @param pin pin to set output
 * 
 * @ingroup freq
 */
void set_master_clock_output_pin(master_clock_output_pin_t pin);

#endif 
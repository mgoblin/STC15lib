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

/**
 * Get MAIN_Fosc value
 * 
 * @return MAIN_Fosc value
 * 
 * @ingroup freq
 */
inline const unsigned long get_master_clock_frequency();

/**
 * Get high part of MAIN_Fosc defined as MAIN_FoscH in sys.h
 * 
 * @return MAIN_FoscH
 * 
 * @ingroup freq
 */
inline const int get_master_clock_frequency_high_part();

/**
 * Get low part of MAIN_Fosc defined as MAIN_FoscL in sys.h
 * 
 * @return MAIN_FoscL
 * 
 * @ingroup freq
 */
inline const int get_master_clock_frequency_low_part();

/**
 * Get master clock frequency divider (CLK_DIV bits [0..2])
 * 
 * @return master clock frequency divider. Divider values range is from 1 to 128.
 * 
 * @see update_and_get_frequency_divider(uint8_t divider_scale)
 * 
 * @ingroup freq
 */
inline uint8_t get_frequency_divider();

/**
 * @brief Update and get master clock frequency divider (CLK_DIV bits [0..2])
 * @details Before setting divider value validate if divider scale is out of range 0..7. 
 * 
 * @param divider_scale scale from 0 to 7 corresponds dividers 1, 2, 4, ...128
 * 
 * @return master clock frequency divider value
 * 
 * @see get_frequency_divider()
 * 
 * @ingroup freq
 */
inline uint8_t update_and_get_frequency_divider(uint8_t divider_scale);

/**
 * Enable master clock output. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
inline void enable_master_clock_output_div1();

/**
 * Enable (master clock output)/2. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
inline void enable_master_clock_output_div2();

/**
 * Enable (master clock output)/4. By default output set to P5.4 pin.
 * 
 * @see disable_master_clock_output()
 * @see set_master_clock_output_pin(master_clock_output_pin pin)    
 * 
 * @ingroup freq
 */
inline void enable_master_clock_output_div4();

/**
 * Disable master clock output
 * 
 * @ingroup freq
 */
inline void disable_master_clock_output();

/**
 * Master clock output pinsf enumeration
 */
typedef enum MasterClockOutputPin
{
    /// output disabled
    NONE, 
    /// output to pin 5.4
    P5_4, 
    /// output to pin 1.6
    P1_6  
} master_clock_output_pin;

/**
 * Get master clock output
 * 
 * @return info about current master clock output
 * 
 * @ingroup freq
 */
inline master_clock_output_pin get_master_clock_output_pin();

/**
 * Set master clock output pin
 * 
 * @param pin pin to set output
 * 
 * @ingroup freq
 */
inline void set_master_clock_output_pin(master_clock_output_pin pin);

#endif 
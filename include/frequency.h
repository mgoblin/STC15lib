#ifndef STC15_FREQH
#define STC15_FREQH

/**
 * @file frequency.h
 * @defgroup freq Frequency
 * @details Functions and data structures for get chip CPU frequency.
 * Chip CPU frequency defined in sys.h as a MAIN_Fosc constant. 
 * @author Michael Golovanov
 */

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
 * @ingroup freq
 */
inline uint8_t get_frequency_divider();

/**
 * @brief Update and get master clock frequency divider (CLK_DIV bits [0..2])
 * @details Before setting divider value validate if divider scale is out of range 0..7. 
 * 
 * @param divider_scale scale from 0 to 7 corresponds dividers 1, 2, 4, ...128
 * 
 * @return master clock frequency divider value/
 * 
 * @ingroup freq
 */
inline uint8_t update_and_get_frequency_divider(uint8_t divider_scale);

#endif 
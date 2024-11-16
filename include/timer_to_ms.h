#ifndef STC15_TIMER_To_MSH
#define STC15_TIMER_To_MSH

/**
 * @file timer_to_ms.h
 * @defgroup timer_to_ms Timer Aux
 * @details Functions and data structures for converting timer ticks to frequency and times.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>

/** @name frequency and ticks
 *  ticks to frequency and vice versa convertions  
 */
///@{

/**
 * @brief Convert ticks to timer frequency.
 * @details The output frequency = (SYSclk/12)/((65536-ticks) * 2)
 * 
 * uint16 ticks used in mode 0, 1, 3.
 * Low byte of ticks is used in mode 2. 
 * 
 * @param ticks timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer_to_ms
 */
uint32_t timer_uint16_ticks_to_freq(uint16_t ticks);

/**
 * @brief Convert timer frequency to ticks. 
 * @details The output frequency = (SYSclk/12)/((65536 - [regs]) * 2)
 * frequency/(SYSclk/12) = 1/((65536- regs) * 2)
 * (((65536- regs) * 2) * frequency)/(SYSclk/12) = 1
 * ((65536- regs) * 2) * frequency = (SYSclk/12)
 * (65536- regs) * 2 = (SYSclk/12) / frequency
 * 65536 - regs = (SYSclk/12) / (2 * frequency)
 * -regs = (SYSclk/12) / (2 * frequency) - 65536
 * regs = 65536 - (SYSclk/12) / (2 * frequency)
 * regs = 65535 - ticks
 * 
 * @ingroup timer_to_ms
 */
uint16_t timer_frequency_to_ticks(uint32_t frequency);

///@}

#endif
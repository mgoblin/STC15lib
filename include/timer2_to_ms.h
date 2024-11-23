#ifndef STC15_TIMER0_TO_MSH
#define STC15_TIMER0_TO_MSH

/**
 * @file timer2_to_ms.h
 * @defgroup timer2_to_ms Timer2 Aux
 * @details Functions and data structures for converting timer ticks 
 * to frequency and times for timer2.
 * 
 * @author Michael Golovanov
*/

#include <stdint.h>
#include <frequency.h>
#include <timer2_mode0.h>
#include <timer_common.h>
#include <timer_to_ms_common.h>

/** @name tick to frequency conversions
 *  Timer ticks to overlow frequency and vice versa convertions 
 */
///@{

/**
 * @brief Convert ticks to timer frequency for timer2 multiplied by 100.
 * @details The output frequency = (SYSclk/timer_clock_divider)/((65536-ticks) * 2).
 * Multiplication by 100 is used for get frequency value without using float numbers.
 * 
 * Call this method after timer2 is initialized and MCU clock frequency divider scale is set.
 * 
 * @param ticks uint16_t timer ticks count to covert
 * 
 * @return uint32_t frequency multiplied by 100 corresponding to ticks count 
 * 
 * @ingroup timer2_to_ms
 */
#define timer2_uint16_ticks_to_freq100(ticks) (timer_uint16_ticks_to_freq100(ticks, get_timer2_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Unsafe approximation timer2 frequency corresponding to ticks. 
 * @details 
 * ticks = get_master_clock_frequency() / (2 * get_timer2_clock_divider() * frequency))
 * 
 * Call this method after timer2 is initialized and MCU clock frequency divider scale is set.
 * 
 * <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param frequency uint32_t frequency value in Hz. Should not be 0;
 * 
 * @return uint16_t timer0 ticks corresponding to frequency value
 * 
 * @ingroup timer2_to_ms
 */
#define timer2_frequency_to_ticks_unsafe(frequency) (timer_frequency_to_ticks_unsafe(frequency, get_timer2_clock_divider(), get_frequency_divider_scale()))

/**
 * @brief Convert ticks count to ms
 * @details <b>This method doesnt analyze corner cases and overflow of result. Be careful.</b> 
 * 
 * @param ticks uint16_t ticks count
 * 
 * @return milliseconds time corresponing to timer ticks
 * 
 * @ingroup timer0_to_ms
 */
#define timer2_ticks_to_ms_usafe(ticks) (timer_ticks_to_ms_usafe(ticks, get_timer0_clock_divider(), get_frequency_divider_scale()))

///@}

/** @name UART baud rate to ticks
 *  UART baud rate to timer ticks to overlow frequency and vice versa convertions 
 */
///@{

/**
 * @brief Calculate timer2 ticks for UART baudrate
 * @details Adapted for use mcu frequency divider. On some baudrates get not exact values.
 * The reasons are 
 * * Formula not get int values
 * * Divisions doesnt support floats and accumulate integer division errors
 * 
 * freq/4 = 2764800
 * | Freq div | Baudrate   | Ticks hex |
 * | ---------| ---------- | --------- |
 * |     1    | 9600       |  0x120    |
 * |     1    | 19200      |  0x90     |
 * |     1    | 38400      |  0x48     |
 * |     1    | 57600      |  0x30     |
 * |     1    | 74880      |  0x25     |
 * |     1    | 115200     |  0x18     |
 * |     1    | 230400     |  0x0C     |
 * |     1    | 250000     |  0x0B     |
 
 * freq / 8 = 1382400
 * | Freq div | Baudrate   | Ticks hex |
 * | ---------| ---------- | --------- |
 * |     2    | 9600       |  0x90     |
 * |     2    | 19200      |  0x48     |
 * |     2    | 38400      |  0x24     |
 * |     2    | 57600      |  0x18     |
 * |     2    | 74880      |  0x12     |
 * |     2    | 115200     |  0x0C     |
 * |     2    | 230400     |  0x06     |
 * |     2    | 250000     | 0x05 0x06?|
 * 
 * freq/16 = 691200
 * | Freq div | Baudrate   | Ticks hex |
 * | ---------| ---------- | --------- |
 * |     4    | 9600       |  0x48     |
 * |     4    | 19200      |  0x24     |
 * |     4    | 38400      |  0x12     |
 * |     4    | 57600      |  0x0C     |
 * |     4    | 74880      |  0x09     |
 * |     4    | 115200     |  0x06     |
 * |     4    | 230400     |  0x03     |
 * |     4    | 250000     | 0x02-0x03?|
 * 
 * 
 * 
 * @param uart_baudrate uint16_t UART baudrate
 * 
 * @return uint16_t timer2 ticks count for UART baudrate
 * 
 * @ingroup timer2_to_ms
 */
uint16_t timer2_mode0_baudrate_to_ticks(uint32_t uart_baudrate); 

///@}

#endif
#ifndef STC15_INTERRUPTSH
#define STC15_INTERRUPTSH

#include<stdbool.h>
#include<sys.h>

/**
 * @file interrupts.h
 * @defgroup interrupts Interrupts
 * 
 * @details Functions and data structures for interrupts.
 * 
 * @author Michael Golovanov
 */

/** 
 * Interrupt priority enumeration
 * 
 * @ingroup interrupts
 */
enum interrupt_priority
{
    /// @brief Low priority
    LOW, 
    /// @brief High priority
    HIGH
};

/**
 * @brief Enable interrupts support of MCU
 * @details Set EA to 1 to enable interrupt support. 
 * By default interrupts support are disabled 
 * Each interrupt should be enabled implicitly by setting its own flag
 *                                                                                               
 * 
 * @ingroup interrupts
 */
void enable_mcu_interrupts();

/**
 * @brief Disable interrupts support of MCU
 * @details Set EA to 0 to disable interrupt support. 
 * By default interrupts support are disabled 
 * Each interrupt should be enabled implicitly by setting its own flag
 *                                                                                               
 * 
 * @ingroup interrupts
 */
void disable_mcu_interrupts();

/**
 * Get MCU interrupts support state
 * 
 * @return if enabled returns true otherwise returns false
 * 
 * @ingroup interrupts
 */
bool is_mcu_interrupts_enabled();

/**
 * @brief Enable low voltage interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_low_voltage_interrupt();

/**
 * @brief Disable low voltage interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_low_voltage_interrupt();

/**
 * @brief Get low voltage interrupt enable status
 * 
 * @ingroup interrupts
 */
bool is_low_voltage_interrupt_enabled();

#endif
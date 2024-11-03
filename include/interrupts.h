#ifndef STC15_INTERRUPTSH
#define STC15_INTERRUPTSH

#include<stdbool.h>
#include<sys.h>

/**
 * @file interrupts.h
 * @defgroup interrupts Interrupts
 * 
 * @details Functions and data structures for interrupts.
 * Interrupts are controlled by registers IE and IE2 bits. 
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
 * @details Get mcu interrupt and low voltage interrupt support status
 * 
 * @return true if mcu and low voltage interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_low_voltage_interrupt_enabled();

/**
 * @brief Enable ADC interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_adc_interrupt();

/**
 * @brief Disable ADC interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_adc_interrupt();

/**
 * @brief Get ADC interrupt enable status
 * @details Get mcu interrupt and ADC interrupt support status
 * 
 * @return true if mcu and ADC interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_adc_interrupt_enabled();

/**
 * @brief Enable UART1 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_uart1_interrupt();

/**
 * @brief Disable UART1 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_uart1_interrupt();

/**
 * @brief Get UART1 interrupt enable status
 * @details Get mcu interrupt and UART1 interrupt support status
 * 
 * @return true if mcu and UART1 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_uart1_interrupt_enabled();

/**
 * @brief Enable INT0 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_int0_interrupt();

/**
 * @brief Disable INT0 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_int0_interrupt();

/**
 * @brief Get INT0 interrupt enable status
 * @details Get mcu interrupt and INT0 interrupt support status
 * 
 * @return true if mcu and INT0 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_int0_interrupt_enabled();

/**
 * @brief Enable INT1 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_int1_interrupt();

/**
 * @brief Disable INT1 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_int1_interrupt();

/**
 * @brief Get INT1 interrupt enable status
 * @details Get mcu interrupt and INT1 interrupt support status
 * 
 * @return true if mcu and INT1 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_int1_interrupt_enabled();

/**
 * @brief Enable timer0 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_timer0_interrupt();

/**
 * @brief Enable timer0 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_timer0_interrupt();

/**
 * @brief Get timer0 interrupt enable status
 * @details Get mcu interrupt and timer0 interrupt support status
 * 
 * @return true if mcu and timer0 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_timer0_interrupt_enabled();

/**
 * @brief Enable timer2 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_timer2_interrupt();

/**
 * @brief Disable timer2 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_timer2_interrupt();

/**
 * @brief Get timer2 interrupt enable status
 * @details Get mcu interrupt and timer2 interrupt support status
 * 
 * @return true if mcu and timer2 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_timer2_interrupt_enabled();

/**
 * @brief Enable SPI interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_spi_interrupt();

/**
 * @brief Disable SPI interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_spi_interrupt();

/**
 * @brief Get SPI interrupt enable status
 * @details Get mcu interrupt and SPI interrupt support status
 * 
 * @return true if mcu and SPI interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_spi_interrupt_enabled();

#endif
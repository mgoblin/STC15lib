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
 * Interrupts at all can be enabled, disabled and readed by 
 * enable_mcu_interrupts(), disable_mcu_interrupts and 
 * is_mcu_interrupts_enabled() routines.
 * 
 * Each kind of interrupt source controlled by 
 * enable_<source>\_interrupt, disable_<source>\_interrupt routines.
 * The state of each kind of interrupt source can be probed by 
 * is_<source>\_interrupts_enabled() routine.
 * If mcu interrupts support not enabled individual interrupt sources are 
 * disabled too and is_<source>\_interrupts_enabled() call return false.
 * 
 * Interrupt handler should be declared as:
 * @code {.c}
 * void interruptHandler() __interrupt(0)
 * @endcode
 * The name of handler routine can be any correct C function name.
 * Hanlder should have empty parameter list. Keyword __interrupt and interrupt number 
 * assign handler to specified interrupt. See STC15series MCU Data Sheet Section 6.4.
 *  
 * \# | Description
 * ---|-----------------------------------------
 * 0  | INT0
 * 1  | Timer0 interrrupt
 * 2  | INT1
 * 3  | Timer1 interrupt (STC15W408AS has no this timer)
 * 4  | UART1 interrupt
 * 5  | ADC interrupt
 * 6  | Low voltage detection (LVD) interrupt
 * 7  | PCA interrupt
 * 8  | UART2 interrupt
 * 9  | SPI interrupt
 * 10 | INT2
 * 11 | INT3 
 * 12 | Timer2 interrupt
 * 13 | PWM interrupt
 * 16 | INT4
 * 17 | S3
 * 18 | S4
 * 19 | Timer3 interrupt (STC15W408AS has no this timer)
 * 20 | Timer4 interrupt (STC15W408AS has no this timer)
 * 21 | Comparator interrupt
 * 
 * @author Michael Golovanov
 */

/** 
 * Interrupt priority enumeration
 * 
 * @ingroup interrupts
 */
typedef enum
{
    /// @brief Low priority
    LOW = 0, 
    /// @brief High priority
    HIGH = 1
} interrupt_priority_t;

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
 * @brief Enable INT2 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_int2_interrupt();

/**
 * @brief Disable INT2 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_int2_interrupt();

/**
 * @brief Get INT2 interrupt enable status
 * @details Get mcu interrupt and INT2 interrupt support status
 * 
 * @return true if mcu and INT2 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_int2_interrupt_enabled();

/**
 * @brief Enable INT3 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_int3_interrupt();

/**
 * @brief Disable INT3 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_int3_interrupt();

/**
 * @brief Get INT3 interrupt enable status
 * @details Get mcu interrupt and INT3 interrupt support status
 * 
 * @return true if mcu and INT3 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_int3_interrupt_enabled();

/**
 * @brief Enable INT4 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void enable_int4_interrupt();

/**
 * @brief Disable INT3 interrupt
 * @details Before call this method mcu interrupt support should be enabled 
 * by calling enable_mcu_interrupts()
 * 
 * @ingroup interrupts
 */
void disable_int4_interrupt();

/**
 * @brief Get INT4 interrupt enable status
 * @details Get mcu interrupt and INT4 interrupt support status
 * 
 * @return true if mcu and INT4 interrupt enabled, otherwise false 
 * 
 * @ingroup interrupts
 */
bool is_int4_interrupt_enable();

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

/**
 * Set programmable counter arrya (PCA) interrupt priority
 * 
 * @param priority interrupt priority
 * 
 * @ingroup interrupts
 */
void set_pca_interrupt_priority(interrupt_priority_t priority);

/**
 * Get programmable counter arrya (PCA) interrupt priority
 * 
 * @return PCA interrupt priority
 * 
 * @ingroup interrupts
 */
interrupt_priority_t get_pca_interrupt_priority();

/**
 * Set low voltage (LVD) interrupt priority
 * 
 * @param priority interrupt priority
 * 
 * @ingroup interrupts
 */
void set_low_voltage_interrupt_priority(interrupt_priority_t priority);

/**
 * Get low voltage interrupt (LVD) priority
 * 
 * @return LVD interrupt priority
 * 
 * @ingroup interrupts
 */
interrupt_priority_t get_low_voltage_interrupt_priority();

/**
 * Set analog to digital converter (ADC) interrupt priority
 * 
 * @param priority interrupt priority
 * 
 * @ingroup interrupts
 */
void set_adc_interrupt_priority(interrupt_priority_t priority);

/**
 * Get analog to digital converter (ADC) interrupt priority
 * 
 * @return ADC interrupt priority
 * 
 * @ingroup interrupts
 */
interrupt_priority_t get_adc_interrupt_priority();

/**
 * Set analog UART1 interrupt priority
 * 
 * @param priority interrupt priority
 * 
 * @ingroup interrupts
 */
void set_uart1_interrupt_priority(interrupt_priority_t priority);

/**
 * Get UART1 interrupt priority
 * 
 * @return UART1 interrupt priority
 * 
 * @ingroup interrupts
 */
interrupt_priority_t get_uart1_interrupt_priority();

#endif
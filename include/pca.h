#ifndef STC15_PCAH
#define STC15_PCAH

/**
 * @file pca.h
 *
 * @defgroup pca PCA/CCP
 *
 * @details Functions and data structures related to PCA module
 *
 * PCA - Programmable Counter Array. It is a 16 bit counter (CH/CL) with
 * three independent compare/capture modules (module 0, 1 and 2). Each module
 * can be configured to work in one of the following modes:
 *
 * - Capture on positive and/or negative edge on the CEXn pin
 * - 16 bit software timer (compare) with optional interrupt
 * - High speed output: toggle CEXn pin on compare match
 * - Pulse width modulator (PWM) output on the CEXn pin
 *
 * PCA counter clock source is selected with pca_set_clock_source() and could be
 * SYSclk with different dividers, Timer0 overflow or external ECI pin.
 *
 * PCA counter overflow (CF flag) and module compare/capture events (CCFn flags)
 * share the single PCA interrupt vector. Use INTERRUPT_PCA from interrupt.h for
 * the interrupt handler.
 *
 * Pin mapping is selected with pca_set_pin_group(). Three pin groups are
 * available and the group selection is stored in P_SW1 register:
 *
 * | Group | ECI   | CCP0  | CCP1  | CCP2  |
 * |-------|-------|-------|-------|-------|
 * | 1     | P1.2  | P1.1  | P1.0  | P3.7  |
 * | 2     | P3.4  | P3.5  | P3.6  | P3.7  |
 * | 3     | P2.4  | P2.5  | P2.6  | P2.7  |
 *
 * PWM output resolution is 8, 7 or 6 bit depending on the module PCA_PWMn
 * register EBSn bits. The datasheet also describes a software technique
 * (section 11.8) which achieves 9..16 bit PWM by combining hardware compare
 * with software updates, it is not implemented by this module.
 *
 * Note: only the STC15W401AS series (which includes STC15W408AS) peripherals
 * are implemented here. The enhanced PWM waveform generator registers
 * (PWMCFG/PWMCR/PWMCKS) defined in STC15Fxx.h belong to the STC15W4K32S4
 * series and are not usable on STC15W401AS devices.
 *
 * @author Michael Golovanov
 */

#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

/** @brief CMOD register CPS0 (counter pulse select) bit position */
#define PCA_CPS0_BIT 1
/** @brief CMOD register CPS (counter pulse select) bits mask */
#define PCA_CPS_MSK 0x0E
/** @brief PCA_PWMn register EBS0 (PWM resolution select) bit position */
#define PCA_PWM_EBS0_BIT 6
/** @brief PCA_PWMn register EBS (PWM resolution select) bits mask */
#define PCA_PWM_EBS_MSK 0xC0

/** @brief P_SW1 register CCP_S0 (CCP pin group select) bit position */
#define PCA_CCP_S0_BIT 4
/** @brief P_SW1 register CCP_S0 (CCP pin group select) bit mask */
#define PCA_CCP_S0_MSK 0x10
/** @brief P_SW1 register CCP_S1 (CCP pin group select) bit mask */
#define PCA_CCP_S1_MSK 0x20
/** @brief P_SW1 register CCP pin group select bits mask */
#define PCA_CCP_SW_MSK (uint8_t)(~(PCA_CCP_S0_MSK | PCA_CCP_S1_MSK))

/**
 * @brief PCA pin group
 *
 * @details describes possible CCP/ECI pin mapping variants.
 * Group selection is done with pca_set_pin_group().
 *
 * @ingroup pca
 */
typedef enum
{
    /** CCP on [P1.2/ECI, P1.1/CCP0, P1.0/CCP1, P3.7/CCP2] */
    PCA_PIN_GROUP_1 = 0,
    /** CCP on [P3.4/ECI_2, P3.5/CCP0_2, P3.6/CCP1_2, P3.7/CCP2_2] */
    PCA_PIN_GROUP_2 = 1,
    /** CCP on [P2.4/ECI_3, P2.5/CCP0_3, P2.6/CCP1_3, P2.7/CCP2_3] */
    PCA_PIN_GROUP_3 = 2
} pca_pin_group_t;

/**
 * @brief PCA counter clock source
 *
 * @details describes possible PCA counter pulse select variants.
 * Clock source selection is done with pca_set_clock_source().
 *
 * @ingroup pca
 */
typedef enum
{
    /** System clock, SYSclk/12 */
    PCA_CLOCK_SYS_12 = 0,
    /** System clock, SYSclk/2 */
    PCA_CLOCK_SYS_2 = 1,
    /** Timer0 overflow pulse */
    PCA_CLOCK_TIMER0 = 2,
    /** External clock at ECI pin, max frequency SYSclk/2 */
    PCA_CLOCK_ECI = 3,
    /** System clock, SYSclk */
    PCA_CLOCK_SYS = 4,
    /** System clock, SYSclk/4 */
    PCA_CLOCK_SYS_4 = 5,
    /** System clock, SYSclk/6 */
    PCA_CLOCK_SYS_6 = 6,
    /** System clock, SYSclk/8 */
    PCA_CLOCK_SYS_8 = 7
} pca_clock_source_t;

/**
 * @brief PCA module PWM output resolution
 *
 * @details describes possible PWM resolutions. Resolution is set with
 * pca_module_pwm_init().
 *
 * Note that the hardware supports only 8, 7 and 6 bit resolutions. The
 * datasheet section 11.8 describes a software technique for 9..16 bit PWM
 * which is not implemented by this module.
 *
 * @ingroup pca
 */
typedef enum
{
    /** Module works as 8 bit PWM */
    PCA_PWM_8BIT = 0,
    /** Module works as 7 bit PWM */
    PCA_PWM_7BIT = 1,
    /** Module works as 6 bit PWM */
    PCA_PWM_6BIT = 2
} pca_pwm_resolution_t;


/** @name pin group
 *  PCA pin mapping functions
 */
///@{

/**
 * @brief Set CCP/ECI pin group
 * @details Select which pins are used as ECI, CCP0, CCP1 and CCP2.
 * Pins are selected with P_SW1 register CCP_S1 and CCP_S0 bits.
 *
 * By default (after MCU power on) pin group 1 is used.
 *
 * @param group pca_pin_group_t pin group to use
 *
 * @ingroup pca
 */
#define pca_set_pin_group(group)                                       \
do {                                                                   \
    bit_clr(P_SW1, PCA_CCP_SW_MSK);                                    \
    bit_set(P_SW1, (uint8_t)((group) << PCA_CCP_S0_BIT));              \
} while(0)

/**
 * @brief Get CCP/ECI pin group
 *
 * @return pca_pin_group_t current pin group
 *
 * @ingroup pca
 */
#define pca_get_pin_group() ((pca_pin_group_t)(bit_shift_right(get_reg(P_SW1, (PCA_CCP_S0_MSK | PCA_CCP_S1_MSK)), PCA_CCP_S0_BIT)))

///@}

/** @name counter
 *  PCA counter functions
 */
///@{

/**
 * @brief Set PCA counter clock source
 * @details Select PCA counter pulse source. Clock source is selected with
 * CMOD register CPS2, CPS1 and CPS0 bits. Other CMOD bits are not changed.
 *
 * @param src pca_clock_source_t clock source
 *
 * @ingroup pca
 */
#define pca_set_clock_source(src)                                      \
do {                                                                   \
    bit_clr(CMOD, (uint8_t)(~PCA_CPS_MSK));                            \
    bit_set(CMOD, (uint8_t)((src) << PCA_CPS0_BIT));                   \
} while(0)

/**
 * @brief Get PCA counter clock source
 *
 * @return pca_clock_source_t current clock source
 *
 * @ingroup pca
 */
#define pca_get_clock_source() ((pca_clock_source_t)(bit_shift_right(get_reg(CMOD, PCA_CPS_MSK), PCA_CPS0_BIT)))

/**
 * @brief Set PCA counter value
 * @details Load 16 bit value into PCA counter CH/CL registers.
 *
 * @param value uint16_t counter value
 *
 * @ingroup pca
 */
#define pca_set_counter(value)                                         \
do {                                                                   \
    CH = (uint8_t)bit_shift_right((uint16_t)(value), 8);               \
    CL = (uint8_t)(value);                                             \
} while(0)

/**
 * @brief Get PCA counter value
 *
 * @return uint16_t PCA counter value
 *
 * @ingroup pca
 */
#define pca_get_counter() ((uint16_t)(bit_shift_left((uint16_t)CH, 8) | (uint16_t)CL))

/**
 * @brief Start PCA counter
 * @details Set CCON register CR bit. Counter starts to count from
 * the current CH/CL value.
 *
 * @ingroup pca
 */
#define pca_start() (CR = 1)

/**
 * @brief Stop PCA counter
 * @details Clear CCON register CR bit.
 *
 * @ingroup pca
 */
#define pca_stop() (CR = 0)

/**
 * @brief Get PCA counter run status
 *
 * @return bool true if counter is running, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_running() (CR)

/**
 * @brief Let PCA counter run in MCU idle mode
 * @details Clear CMOD register CIDL bit. By default counter is gated off
 * in idle mode.
 *
 * @ingroup pca
 */
#define pca_counter_run_in_idle() (bit_clr(CMOD, CBIT7))

/**
 * @brief Gate off PCA counter in MCU idle mode
 * @details Set CMOD register CIDL bit.
 *
 * @ingroup pca
 */
#define pca_counter_gate_off_in_idle() (bit_set(CMOD, SBIT7))

/**
 * @brief Get PCA counter idle mode status
 *
 * @return bool true if counter is gated off in idle mode, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_counter_gated_off_in_idle() (test_if_bit_set(CMOD, SBIT7))

///@}

/** @name overflow
 *  PCA counter overflow flag and interrupt functions
 */
///@{

/**
 * @brief Clear PCA counter overflow flag
 * @details Clear CCON register CF bit. CF flag should be cleared by software.
 *
 * @ingroup pca
 */
#define pca_clear_overflow_flag() (CF = 0)

/**
 * @brief Get PCA counter overflow flag status
 *
 * @return bool true if counter overflow occurred, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_overflow() (CF)

/**
 * @brief Enable PCA counter overflow interrupt
 * @details Set CMOD register ECF bit. When enabled the CF flag generates
 * PCA interrupt. Before call this method mcu interrupt support should be
 * enabled by calling enable_mcu_interrupts()
 *
 * @ingroup pca
 */
#define pca_enable_overflow_interrupt() (bit_set(CMOD, SBIT0))

/**
 * @brief Disable PCA counter overflow interrupt
 * @details Clear CMOD register ECF bit.
 *
 * @ingroup pca
 */
#define pca_disable_overflow_interrupt() (bit_clr(CMOD, CBIT0))

/**
 * @brief Get PCA counter overflow interrupt enable status
 *
 * @return bool true if overflow interrupt is enabled, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_overflow_interrupt_enabled() (test_if_bit_set(CMOD, SBIT0))

///@}

/** @name module flags
 *  PCA module compare/capture flag functions
 */
///@{

/**
 * @brief Clear PCA module compare/capture flag
 * @details Clear CCON register CCFn bit for given module.
 * CCFn flags should be cleared by software.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_clear_module_flag(module) (CCF ## module = 0)

/**
 * @brief Get PCA module compare/capture flag status
 * @details Get CCON register CCFn bit for given module.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @return bool true if match or capture occurred, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_module_flag_set(module) (CCF ## module)

/**
 * @brief Enable PCA module compare/capture interrupt
 * @details Set CCAPMn register ECCFn bit for given module. When enabled the
 * CCFn flag generates PCA interrupt. Before call this method mcu interrupt
 * support should be enabled by calling enable_mcu_interrupts()
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_enable_interrupt(module) (bit_set(CCAPM ## module, SBIT0))

/**
 * @brief Disable PCA module compare/capture interrupt
 * @details Clear CCAPMn register ECCFn bit for given module.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_disable_interrupt(module) (bit_clr(CCAPM ## module, CBIT0))

/**
 * @brief Get PCA module compare/capture interrupt enable status
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @return bool true if module interrupt is enabled, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_module_interrupt_enabled(module) (test_if_bit_set(CCAPM ## module, SBIT0))

///@}

/** @name compare/capture
 *  PCA module compare and capture functions
 */
///@{

/**
 * @brief Enable PCA module comparator
 * @details Set CCAPMn register ECOMn bit. Comparator should be enabled for
 * compare, toggle and PWM modes.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_enable_comparator(module) (bit_set(CCAPM ## module, SBIT6))

/**
 * @brief Disable PCA module comparator
 * @details Clear CCAPMn register ECOMn bit.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_disable_comparator(module) (bit_clr(CCAPM ## module, CBIT6))

/**
 * @brief Enable capture on positive edge
 * @details Set CCAPMn register CAPPn bit. Capture occurs on positive edge
 * on CEXn pin. Capture and PWM modes could not be used simultaneously.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_enable_capture_positive(module) (bit_set(CCAPM ## module, SBIT5))

/**
 * @brief Disable capture on positive edge
 * @details Clear CCAPMn register CAPPn bit.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_disable_capture_positive(module) (bit_clr(CCAPM ## module, CBIT5))

/**
 * @brief Enable capture on negative edge
 * @details Set CCAPMn register CAPNn bit. Capture occurs on negative edge
 * on CEXn pin. Capture and PWM modes could not be used simultaneously.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_enable_capture_negative(module) (bit_set(CCAPM ## module, SBIT4))

/**
 * @brief Disable capture on negative edge
 * @details Clear CCAPMn register CAPNn bit.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_disable_capture_negative(module) (bit_clr(CCAPM ## module, CBIT4))

/**
 * @brief Enable PCA module match
 * @details Set CCAPMn register MATn bit. When enabled a match of the PCA
 * counter with module compare/capture register sets CCFn flag.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_enable_match(module) (bit_set(CCAPM ## module, SBIT3))

/**
 * @brief Disable PCA module match
 * @details Clear CCAPMn register MATn bit.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_disable_match(module) (bit_clr(CCAPM ## module, CBIT3))

/**
 * @brief Enable PCA module toggle output
 * @details Set CCAPMn register TOGn bit. When enabled a match of the PCA
 * counter with module compare/capture register toggles CEXn pin.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_enable_toggle(module) (bit_set(CCAPM ## module, SBIT2))

/**
 * @brief Disable PCA module toggle output
 * @details Clear CCAPMn register TOGn bit.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_disable_toggle(module) (bit_clr(CCAPM ## module, CBIT2))

/**
 * @brief Set PCA module compare/capture value
 * @details Load 16 bit value into module CCAPnH/CCAPnL registers.
 * In compare mode this value is compared with the PCA counter.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 * @param value uint16_t compare value
 *
 * @ingroup pca
 */
#define pca_module_set_compare(module, value)                          \
do {                                                                   \
    CCAP ## module ## H = (uint8_t)bit_shift_right((uint16_t)(value), 8); \
    CCAP ## module ## L = (uint8_t)(value);                            \
} while(0)

/**
 * @brief Get PCA module capture value
 * @details Read 16 bit value from module CCAPnH/CCAPnL registers.
 * In capture mode this value is the PCA counter value captured on CEXn pin
 * edge.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @return uint16_t capture value
 *
 * @note The capture registers have no read latch, so a capture that happens
 * between the two byte reads can produce a value made of one old byte and one
 * new byte. Clear the CCFn flag before reading to make this window as small as
 * possible. If the capture rate is high enough for this to matter, read the
 * value in the PCA interrupt handler.
 *
 * @ingroup pca
 */
#define pca_module_get_capture(module) ((uint16_t)(bit_shift_left((uint16_t)CCAP ## module ## H, 8) | (uint16_t)CCAP ## module ## L))

///@}

/** @name pwm
 *  PCA module pulse width modulator functions
 */
///@{

/**
 * @brief Init PCA module in PWM mode
 * @details Set PWM output resolution with module PCA_PWMn register EBSn bits
 * and enable PWM output by setting CCAPMn register PWMn bit.
 *
 * PWM resolution could be 8, 7 or 6 bit. Note that PWMn and CAPPn/CAPNn bits
 * should not be set simultaneously.
 *
 * Before PWM output is started the module pin should be configured as
 * push-pull output and the CEXn pin function should be selected with
 * pca_set_pin_group().
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 * @param resolution pca_pwm_resolution_t PWM resolution
 *
 * @ingroup pca
 */
#define pca_module_pwm_init(module, resolution)                        \
do {                                                                   \
    bit_clr(PCA_PWM ## module, (uint8_t)(~PCA_PWM_EBS_MSK));           \
    bit_set(PCA_PWM ## module, (uint8_t)((resolution) << PCA_PWM_EBS0_BIT)); \
    bit_set(CCAPM ## module, SBIT1);                                   \
} while(0)

/**
 * @brief Disable PCA module PWM output
 * @details Clear CCAPMn register PWMn bit.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @ingroup pca
 */
#define pca_module_pwm_disable(module) (bit_clr(CCAPM ## module, CBIT1))

/**
 * @brief Get PCA module PWM output enable status
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 *
 * @return bool true if PWM output is enabled, otherwise false
 *
 * @ingroup pca
 */
#define is_pca_module_pwm_enabled(module) (test_if_bit_set(CCAPM ## module, SBIT1))

/**
 * @brief Set PCA module PWM duty
 * @details Load duty value into module CCAPnH/CCAPnL registers. CCAPnH is
 * a reload register and it is loaded into CCAPnL on PCA counter overflow, so
 * new duty value is applied without glitch on PWM output.
 *
 * Duty value range depends on selected PWM resolution: 0..255 for 8 bit PWM,
 * 0..127 for 7 bit PWM and 0..63 for 6 bit PWM.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 * @param duty uint8_t PWM duty value
 *
 * @ingroup pca
 */
#define pca_module_pwm_set_duty(module, duty)                          \
do {                                                                   \
    CCAP ## module ## H = (uint8_t)(duty);                             \
    CCAP ## module ## L = (uint8_t)(duty);                             \
} while(0)

/**
 * @brief Set PCA module PWM duty without immediate update
 * @details Load duty value into module CCAPnH reload register only. New duty
 * value is applied on next PCA counter overflow. Use this method to change
 * duty synchronously with PWM period.
 *
 * @param module uint8_t PCA module number 0, 1 or 2
 * @param duty uint8_t PWM duty value
 *
 * @ingroup pca
 */
#define pca_module_pwm_set_duty_on_overflow(module, duty) (CCAP ## module ## H = (uint8_t)(duty))

///@}

#endif

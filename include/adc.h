#ifndef STC15_ADCH
#define STC15_ADCH

/**
 * @file adc.h
 * 
 * @defgroup adc ADC
 * 
 * @details Functions and data structures related to ADC module
 * 
 * @author Michael Golovanov
 */

#include <sys.h>
#include <bits.h>
#include <stdint.h>
#include <stdbool.h>

/**
 * @brief ADC P1 modes enum
 * 
 * @details describes P1 pin modes for ADC
 * 
 * ADC can be used only with P1 pins. Each P1 pin can be configured as ADC input.
 * P1 pins can be configured as input only or open-drain.
 * 
 * @ingroup adc
 */
typedef enum 
{
    /** @brief input only P1 pin mode */
    PIN_INPUT_ONLY,
    /** @brief open drain P1 pin mode */
    PIN_OPEN_DRAIN,
} adc_pin_mode_t;

/**
 * 
 * @brief ADC speed enum
 * 
 * @details describes possible convertion speeds
 * 
 * @ingroup adc
 */
typedef enum 
{
    /** 540 mcu cycles */
    ADC_SPEED_540 = 0b00000000,
    /** 360 mcu cycles */
    ADC_SPEED_360 = 0b00100000,
    /** 180 mcu cycles */
    ADC_SPEED_180 = 0b01000000,
    /** 90 mcu cycles */
    ADC_SPEED_90  = 0b01100000
} adc_speed_t;

/**
 * 
 * @brief ADC initialization function
 * 
 * @details Configures the ADC for 10-bit resolution, uses the internal 
 * voltage reference. 
 *
 * 
 * @param p1_pin uint8_t P1 pin number. Values from 0 to 7.
 * @param pin_mode adc_pin_mode_t P1 pin mode. 
 * @param adrj_flag bool ADC_RES-ADC_RESL or ADC_RESL-ADC_RES result bits order
 * @param speed adc_speed_t ADC convertion speed
 * 
 * @ingroup adc
 */
void adc_init(uint8_t p1_pin, adc_pin_mode_t pin_mode, bool adrj_flag, adc_speed_t speed);
uint16_t adc_read(void);
void adc_destroy(void);

#endif
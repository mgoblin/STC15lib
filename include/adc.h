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
#include <gpio.h>

/** @brief ADC CONTR register ADC_START bit position */
#define ADC_START_BIT 3
/** @brief ADC CONTR register ADC_FLAG bit position */
#define ADC_FLAG_BIT 4
/** @brief CLKDIV register ADRJ bit position */
#define ADRJ_BIT 5
/** ADC CONTR register ADC_POWER_ON bit mask */
#define ADC_POWER_ON_MSK 0x80

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
#define adc_init(p1_pin, pin_mode, adrj_flag, speed)    \
{                                                       \
    /* Set input only or open drain pin mode */         \
    /* according to pin_mode argument */                \
    switch (pin_mode)                                   \
    {                                                   \
        case PIN_OPEN_DRAIN:                            \
            pin_open_drain_init(P1, p1_pin);            \
            break;                                      \
        case PIN_INPUT_ONLY:                            \
            pin_input_only_init(P1,p1_pin);             \
            break;                                      \
        default:                                        \
            pin_input_only_init(P1,p1_pin);             \
            break;                                      \
    }                                                   \
                                                        \
    /* Set P1ASF bit for using pin as ADC input */      \
    bit_set(P1ASF, 1 << p1_pin);                        \
                                                        \
    /* Set ADC power on, speed and source channel pin */\
    ADC_CONTR = ADC_POWER_ON_MSK | p1_pin | speed;      \
                                                        \
    /* Set ADC_RES-ADC_RESL or ADC_RESL-ADC_RES */      \
    /* result bits order */                             \
    if (adrj_flag)                                      \
    {                                                   \
        bit_set(CLK_DIV, 1 << ADRJ_BIT);                \
    }                                                   \
    else                                                \
    {                                                   \
        bit_clr(CLK_DIV, ~(1 << ADRJ_BIT));             \
    }                                                   \
}

uint16_t adc_read(void);
void adc_destroy(void);

#endif
#ifndef STC15_ADCH
#define STC15_ADCH

/**
 * @file adc.h
 * 
 * @defgroup adc ADC
 * 
 * @details Functions and data structures related to ADC module
 * 
 * TODO Describe sync and async modes
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

/** @brief ADC result shift offset */
#define ADC_LOW_BITS_COUNT 2
/** @brief ADC result low bits mask */
#define ADC_LOW_BITS_MSK 0x03

/**
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
 * @brief ADC initialization in pin input only mode
 * 
 * @details Configures the ADC for 10-bit resolution, uses the internal 
 * voltage reference. 
 *
 * 
 * @param p1_pin uint8_t P1 pin number. Values from 0 to 7.
 * @param adrj_flag bool ADC_RES-ADC_RESL or ADC_RESL-ADC_RES result bits order
 * @param speed adc_speed_t ADC convertion speed
 * 
 * @ingroup adc
 */
#define adc_init_input_only(p1_pin, adrj_flag, speed)   \
do {                                                    \
    /* Set input only pin mode */                       \
    pin_input_only_init(P1, p1_pin);                    \
                                                        \
    /* Set P1ASF bit for using pin as ADC input */      \
    bit_set(P1ASF, 1 << p1_pin);                        \
                                                        \
    /* Set ADC power on, speed and source channel pin */\
    ADC_CONTR = ADC_POWER_ON_MSK | p1_pin | speed;      \
                                                        \
    /* Set ADC_RES-ADC_RESL or ADC_RESL-ADC_RES */      \
    /* result bits order */                             \
    adrj_flag ?                                         \
        bit_set(CLK_DIV, 1 << ADRJ_BIT) :               \
        bit_clr(CLK_DIV, ~(1 << ADRJ_BIT));             \
} while(0)

/**
 * @brief ADC initialization in pin open drain mode
 * 
 * @details Configures the ADC for 10-bit resolution, uses the internal 
 * voltage reference. 
 *
 * 
 * @param p1_pin uint8_t P1 pin number. Values from 0 to 7.
 * @param adrj_flag bool ADC_RES-ADC_RESL or ADC_RESL-ADC_RES result bits order
 * @param speed adc_speed_t ADC convertion speed
 * 
 * @ingroup adc
 */
#define adc_init_open_drain(p1_pin, adrj_flag, speed)   \
do {                                                    \
    /* Set input only pin mode */                       \
    pin_open_drain_init(P1, p1_pin);                    \
                                                        \
    /* Set P1ASF bit for using pin as ADC input */      \
    bit_set(P1ASF, 1 << p1_pin);                        \
                                                        \
    /* Set ADC power on, speed and source channel pin */\
    ADC_CONTR = ADC_POWER_ON_MSK | p1_pin | speed;      \
                                                        \
    /* Set ADC_RES-ADC_RESL or ADC_RESL-ADC_RES */      \
    /* result bits order */                             \
    adrj_flag ?                                         \
        bit_set(CLK_DIV, 1 << ADRJ_BIT) :               \
        bit_clr(CLK_DIV, ~(1 << ADRJ_BIT));             \
} while(0)

/**
 * @brief ADC read routine
 * 
 * @details Clear result ready ADC flag and start ADC.
 * Waiting for result is ready (flag up).
 * After ADC flag is up by hardware store result to 
 * value reference
 * 
 * @param value uint16_t 10-bit ADC result  
 * 
 * @ingroup adc
 */
#define adc_read_sync(value)                            \
do {                                                    \
    /* Clear ADC result ready flag */                   \
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT));           \
    /* Set ADC power on */                              \
    bit_set(ADC_CONTR, 1 << ADC_START_BIT);             \
                                                        \
    /* Waiting for ADC result is ready */               \
    while (test_if_bit_cleared(ADC_CONTR, 1 << ADC_FLAG_BIT));  \
                                                        \
    /* Return ADC result value */                       \
    *value = test_if_bit_set(CLK_DIV, 1 << ADRJ_BIT) ?  \
        (ADC_RESL << ADC_LOW_BITS_COUNT) | (ADC_RES & ADC_LOW_BITS_MSK)  \
        :                                               \
        (ADC_RES << ADC_LOW_BITS_COUNT)  | (ADC_RESL & ADC_LOW_BITS_MSK);\
} while(0)

/**
 * @brief Start async ADC read operation if not started
 * 
 * @details Set ADC start flag if it does not set
 * After that program is not bloked. When result 
 * is ready MCU generate ADC interrupt.    
 * 
 * @note ADC interrupt should be enabled
 * 
 * @ingroup adc
 */
#define adc_async_read_start()                          \
do {                                                    \
    if (!is_adc_async_read_started())                   \
    {                                                   \
        bit_set(ADC_CONTR, 1 << ADC_START_BIT);         \
    }                                                   \
} while(0);

/**
 * @brief get ADC start and power flags
 * 
 * @return bool true if flags set otherwise false
 * 
 * @ingroup adc
 */
#define is_adc_async_read_started() (test_if_bit_set(ADC_CONTR, 1 << ADC_START_BIT) && (ADC_CONTR & ADC_POWER_ON_MSK))

/**
 * @brief Clear ADC result ready flag
 * 
 * @note This routine suppose to be called inside ADC interrupt handler
 * 
 * @ingroup adc
 */
#define adc_async_read_finish() (bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT)))

uint16_t adc_async_get_result(void);



/**
 * @brief Deinitialize ADC module
 * 
 * Stops ongoing conversion, clears status flag, and disables analog function 
 * on all P1 pins.
 * 
 * @ingroup adc
 */
#define adc_destroy(void)                               \
do {                                                    \
    /* Stop ADC */                                      \
    bit_clr(ADC_CONTR, ~(1 << ADC_START_BIT));          \
    /* Clear ADC result ready flag */                   \
    bit_clr(ADC_CONTR, ~(1 << ADC_FLAG_BIT));           \
                                                        \
    /* Set all gpio P1 port pins */                     \
    /* as general purpose pins mode */                  \
    P1ASF = 0;                                          \
                                                        \
    /* ADC power off*/                                  \
    bit_clr(ADC_CONTR, ~ADC_POWER_ON_MSK);              \
} while(0)

#endif
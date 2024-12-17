#ifndef STC15_PINH
#define STC15_PINH
/**
 * @file pin.h
 * 
 * @defgroup pin Pin
 * 
 * @details Pin modes data structures and routines
 * 
 * @author Michael Golovanov
 */

#include <sys.h>
#include <bits.h>
#include <stdint.h>

/**
 * @brief Pin in/out modes enum
 * 
 * @ingroup pin
 */
typedef enum
{
    /**  
     * @brief Quasi bidirectional mode. 
     * @details 
     * Pin can be used for read and write digital data.
     * Sink Current up to 20mA, pull-up Current is 270μA. 
     * Because of manufactured error, the actual pull-up current is 270uA ~ 150uA
     *  
     * */
    QUASI_BIDIRECTIONAL,

    /**
     * @brief Strong pull-up output 
     * @details 
     * Current can be up to 20mA, 
     * resistors need to be added to restrict current
     */
    PUSH_PULL,

    /**
     * @brief input-only (high-impedance)
     * 
     */
    INPUT_ONLY,

    /**  
     * @brief Open drain mode. 
     * @details 
     * Internal pull-up resistors should be disabled and external 
     * pull-up resistors need to join 
     * */
    OPEN_DRAIN
} pin_mode_t;

/**
 * @brief Init pin in in QUASI_BIDIRECTIONAL mode
 * @details QUASI_BIDIRECTIONAL mode is default pin mode and set after
 * MCU power on 
 * 
 * Set mode for pin in port. For example for pin P10 call this routine with 
 * P1, 0 arguments 
 * 
 * @port pin port for example P1, P3 and etc
 * 
 * @ingroup pin
 */
#define pin_quasi_bidiretional_init(port, port_pin)             \
{                                                               \
    bit_clr(port ## M1, ~(1 << port_pin));                      \
    bit_clr(port ## M0, ~(1 << port_pin));                      \
}

#endif
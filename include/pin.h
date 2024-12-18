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
#include <stdbool.h>

/**
 * @brief Init pin in in QUASI_BIDIRECTIONAL mode
 * @details QUASI_BIDIRECTIONAL mode is default pin mode and set after
 * MCU power on 
 * 
 * Set mode for pin in port. For example for pin P10 call this routine with 
 * P1, 0 arguments 
 * 
 * @param port pin port for example P1, P3 and etc
 * @param port_pin uint8_t pin mumber in port 0..7 
 * 
 * @ingroup pin
 */
#define pin_quasi_bidiretional_init(port, port_pin)             \
{                                                               \
    bit_clr(port ## M1, ~(1 << port_pin));                      \
    bit_clr(port ## M0, ~(1 << port_pin));                      \
}

/**
 * @brief Init pin in in PUSH_PULL mode
 * @details 
 * Push-pull output(strong pull-up output，current can be up to 20mA, 
 * resistors need to be added to restrict current 
 * 
 * Set mode for pin in port. For example for pin P10 call this routine with 
 * P1, 0 arguments 
 * 
 * @param port pin port for example P1, P3 and etc
 * @param port_pin uint8_t pin mumber in port 0..7 
 * 
 * @ingroup pin
 */
#define pin_push_pull_init(port, port_pin)                      \
{                                                               \
    bit_clr(port ## M1, ~(1 << port_pin));                      \
    bit_set(port ## M0, 1 << port_pin);                         \
}

/**
 * @brief Init pin in in INPUT_ONLY mode
 * @details Input only output have high impedance 
 * 
 * Set mode for pin in port. For example for pin P10 call this routine with 
 * P1, 0 arguments 
 * 
 * @param port pin port for example P1, P3 and etc
 * @param port_pin uint8_t pin mumber in port 0..7 
 * 
 * @ingroup pin
 */
#define pin_input_only_init(port, port_pin)                     \
{                                                               \
    bit_set(port ## M1, 1 << port_pin);                         \
    bit_clr(port ## M0, ~(1 << port_pin));                      \
}

/**
 * @brief Init pin in in OPEN_DRAIN mode
 * @details internal pull-up resistors should be disabled 
 * and external pull-up resistors need to join. 
 * 
 * Set mode for pin in port. For example for pin P10 call this routine with 
 * P1, 0 arguments 
 * 
 * @param port pin port for example P1, P3 and etc
 * @param port_pin uint8_t pin mumber in port 0..7 
 * 
 * @ingroup pin
 */
#define pin_open_drain_init(port, port_pin)                     \
{                                                               \
    bit_set(port ## M1, 1 << port_pin);                         \
    bit_set(port ## M0, 1 << port_pin);                         \
}

/**
 * @brief Assert pin in quasy-bidirectional mode
 * 
 * @return true if pin in quasy-bidirectional mode, otherwise false
 * 
 * @ingroup pin
 */
#define is_pin_mode_quasi_bidiretional(port, port_pin)  ( ((port ## M1 & (1 << port_pin)) == 0) && ((port ## M0 & (1 << port_pin)) == 0 ) )

/**
 * @brief Assert pin in push-pull mode
 * 
 * @return true if pin in push-pull mode, otherwise false
 * 
 * @ingroup pin
 */
#define is_pin_mode_push_pull(port, port_pin)           ( ((port ## M1 & (1 << port_pin)) == 0) && ((port ## M0 & (1 << port_pin)) != 0) )

/**
 * @brief Assert pin in input-only mode
 * 
 * @return true if pin in input-only mode, otherwise false
 * 
 * @ingroup pin
 */
#define is_pin_mode_input_only(port, port_pin)          ( ((port ## M1 & (1 << port_pin)) != 0) && ((port ## M0 & (1 << port_pin)) == 0) )

/**
 * @brief Assert pin in open-drain mode
 * 
 * @return true if pin in open-drain mode, otherwise false
 * 
 * @ingroup pin
 */
#define is_pin_mode_open_drain(port, port_pin)          ( ((port ## M1 & (1 << port_pin)) != 0) && ((port ## M0 & (1 << port_pin)) != 0) )

#endif
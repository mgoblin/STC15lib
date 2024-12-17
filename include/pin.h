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

void pinMode(__sbit pin, pin_mode_t mode);

#endif
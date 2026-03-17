#ifndef STC15_COMPARATORH
#define STC15_COMPARATORH

#include <sys.h>
#include <interrupt.h>

/**
 * @file comparator.h
 * @defgroup comparator Comparator
 * @details Functions and data structures related to comparator
 * 
 * Comparator is used for analog comparation of positive and negative inputs.
 * 
 * Comparator could work in async (using interrupts) or sync modes.
 * 
 * @author Michael Golovanov
 */

 /**
  * @brief Comparator init for using interrupts routine
  * 
  * @ingroup comparator
  */
#define comparator_init_async()             \
do {                                        \
    CMPCR1 = 0x00;                          \
    CMPCR2 = 0x09;                          \
                                            \
    enable_mcu_interrupts();                \
    enable_comparator_interrupt(ANY_EDGE);  \
} while(0)    

/**
 * @brief Comparator start routine
 * @details Before call this method comparator should be initialized 
 * by comparator_init_async() or comparator_init_sync()
 * 
 * @ingroup comparator
 */
#define comparator_start() (bit_set(CMPCR1, SBIT7))

/**
 * @brief Comparator stop routine
 * @details Before call this method comparator should be started 
 * by calling comparator_start()
 * 
 * @ingroup comparator
 */
#define comparator_stop() (bit_clr(CMPCR1, CBIT7))

#endif
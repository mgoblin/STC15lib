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

void comparator_start(void);

void comparator_stop(void);

#endif
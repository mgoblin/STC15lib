#ifndef STC15_COMPARATORH
#define STC15_COMPARATORH

#include <sys.h>
#include <interrupt.h>

/**
 * @file comparator.h
 * @defgroup comparator Comparator
 * @details Functions and data structures related to comparator
 * 
 * Comparator is used for analog compare of positive and negative inputs.
 * 
 * Comparator could work in async (using interrupts) or sync modes.
 * 
 * @author Michael Golovanov
 */

/**
 * @brief Comparator enable bit position
 */
#define CMP_ENABLE_BIT_POS 7
/**
 * @brief Comparator enable bit mask
 */
#define CMP_ENABLE_BIT_MASK bit_mask(CMP_ENABLE_BIT_POS)
/**
 * @brief Comparator enable bit
 */
#define CMP_ENABLE_BIT (CMP_ENABLE_BIT_MASK)

/** @brief CMPCR1 register value after reset */
#define CMPCR1_DEFAULT_VALUE 0x00
/** @brief CMPCR2 register value after reset */
#define CMPCR2_DEFAULT_VALUE 0x09

 /**
  * @brief Comparator init for using interrupts routine
  * 
  * @ingroup comparator
  */
#define comparator_init_async()             \
do {                                        \
    CMPCR1 = CMPCR1_DEFAULT_VALUE;          \
    CMPCR2 = CMPCR2_DEFAULT_VALUE;          \
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
#define comparator_start() (bit_set(CMPCR1, CMP_ENABLE_BIT))

/**
 * @brief Comparator stop routine
 * @details Before call this method comparator should be started 
 * by calling comparator_start()
 * 
 * @ingroup comparator
 */
#define comparator_stop() (bit_clr(CMPCR1, CMP_ENABLE_BIT))

#endif
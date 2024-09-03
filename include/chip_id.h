#ifndef STC15_CHIPIDH
#define STC15_CHIPIDH

/**
 * @file chip_id.h
 * @defgroup chip_id ChipID
 * @details Functions and data structures related to chip id
 * @author Michael Golovanov
 */

#include <stdint.h>

/**
 * Size of chip id array  
 */ 
#define ID_SIZE 7

/**
 * Get chip id as array. Array size is ID_SIZE
 * 
 * @return chip id array
 * 
 * @ingroup chip_id
 */
uint8_t* get_chipid();

#endif
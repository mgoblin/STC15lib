#ifndef STC15_CHIPIDH
#define STC15_CHIPIDH

/**
 * @file chip_id.h
 * @defgroup chip_id ChipID
 * @details Functions and data structures related to chip id
 * 
 * @example chip_id_example.c
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>
#include <sys.h>

/**
 * @brief Size of chip id array
 * 
 * @ingroup chip_id  
 */ 
#define CHIP_ID_SIZE 7

/**
 * @brief Chip id address in flash memory
 * 
 * @ingroup chip_id
 */
#define CHIP_ID_ADDR_ROM 0x1ff9

/**
 * @brief First byte of chip id in flash. 
 * 
 * @details Size of chip id is CHIP_ID_SIZE
 * 
 * Example: @include chip_id_example.c
 * 
 * @ingroup chip_id
 */
__code __at(CHIP_ID_ADDR_ROM) uint8_t chip_id;

/**
 * @brief Get chip id as array. Array size is ID_SIZE
 * 
 * @param cid array of CHIP_ID_SIZE
 * @return filled chip id array
 * 
 * @ingroup chip_id
 */
#define get_chipid(cid) {                       \
    const uint8_t *id = &chip_id;               \
    for(uint8_t i = 0; i < CHIP_ID_SIZE; i++)   \
    {                                           \
        cid[i] = id[i];                         \
    }                                           \
}

#endif
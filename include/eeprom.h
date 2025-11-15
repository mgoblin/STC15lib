#ifndef STC15_EEPROMH
#define STC15_EEPROMH

/**
 * @file eeprom.h
 * @defgroup eeprom EEPROM
 * @details Functions and data structures related to EEPROM
 * 
 * @author Michael Golovanov
 */

#include <stdint.h>

#include <sys.h>

/**
 * @brief Read operation
 * 
 * @ingroup eeprom
 */
#define REAP_OP 0x01

/**
 * @brief Read operation trigger sequence first byte
 * 
 * @ingroup eeprom
 */
#define READ_OP_TRIGGER_SEQ_FIRST_BYTE 0x5A
/**
 * @brief Read operation trigger sequence first byte
 * 
 * @ingroup eeprom
 */
#define READ_OP_TRIGGER_SEQ_SECOND_BYTE 0xA5

/**
 * @brief Reads single byte from the EEPROM at the given address
 * 
 * This function performs a read operation from the EEPROM using the provided
 * high and low bytes of the address. The data read from the EEPROM is stored 
 * in the location pointed to by 'value_ptr'. 
 * For reading from the EEPROM IAP registers are used.
 *
 * @param addr_high High byte of the EEPROM address to read from.
 * @param addr_low  Low byte of the EEPROM address to read from.
 * @param value_ptr Pointer to a uint8_t variable where the read value will be stored.
 *                  Must not be NULL.
 * @param error_ptr Pointer to a uint8_t variable where the error status will be stored.
 *                  Must not be NULL. 0 - no error, otherwise - error code
 * 
 * @ingroup eeprom
 */
void eeprom_read_byte(
    uint8_t addr_high, 
    uint8_t addr_low, 
    uint8_t* value_ptr,
    uint8_t* error_ptr
);

#endif
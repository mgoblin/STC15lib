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
 *
 * @return Status of the read operation. Returns 0 on success, or an error code 
 *         if the operation failed.
 *
 * 
 * @ingroup eeprom
 */
uint8_t eeprom_read_byte(uint8_t addr_high, uint8_t addr_low, uint8_t* value_ptr);

#endif
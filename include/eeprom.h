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
#include <bits.h>

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
#define eeprom_read_byte(addr_high, addr_low, value_ptr, error_ptr)     \
do {                                                                    \
    /* Enable IAP */                                                    \
    bit_set(IAP_CONTR, SBIT7);                                          \
                                                                        \
    /* Set address */                                                   \
    IAP_ADDRH = addr_high;                                              \
    IAP_ADDRL = addr_low;                                               \
                                                                        \
    /* Set read operation */                                            \
    IAP_CMD = REAP_OP;                                                  \
                                                                        \
    /* Set start read sequence */                                       \
    IAP_TRIG = READ_OP_TRIGGER_SEQ_FIRST_BYTE;                          \
    IAP_TRIG = READ_OP_TRIGGER_SEQ_SECOND_BYTE;                         \
                                                                        \
    /* Wait for IAP finish */                                           \
    NOP();                                                              \
    NOP();                                                              \
    NOP();                                                              \
                                                                        \
    /* Read data from IAP */                                            \
    *value_ptr = IAP_DATA;                                              \
    /* Read error status from IAP */                                    \
    *error_ptr = get_bit(IAP_CONTR, 4);                                 \
                                                                        \
    /* Disable IAP */                                                   \
    bit_clr(IAP_CONTR, CBIT7);                                          \
} while (0)

#endif
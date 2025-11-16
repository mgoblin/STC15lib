#ifndef STC15_EEPROMH
#define STC15_EEPROMH

/**
 * @file eeprom.h
 * @defgroup eeprom EEPROM
 * @details Functions and data structures related to EEPROM
 * 
 * @author Michael Golovanov
 */

#include <assert.h>
#include <stdint.h>

#include <sys.h>
#include <bits.h>
#include <power_management.h>

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
 * @brief Read operation trigger sequence second byte
 * 
 * @ingroup eeprom
 */
#define READ_OP_TRIGGER_SEQ_SECOND_BYTE 0xA5

/**
 * @brief Command fail error code
 * 
 * @ingroup eeprom
 */
#define CMD_FAIL_BIT 4

/**
 * @brief Return codes. Operation success
 * 
 * @ingroup eeprom
 */
#define CMD_SUCCESS 0

/**
 * @brief Return codes. Operation fail
 * 
 * @ingroup eeprom
 */
#define CMD_FAIL_ERROR 1

/**
 * @brief Return codes. Low voltage error
 * 
 * @ingroup eeprom
 */
#define LOW_VOLTAGE_ERROR 2

/**
 * @brief Error value
 * 
 * @ingroup eeprom
 */
#define ERROR_VALUE 0xFF

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
 *                  Must not be NULL. If read operation fails, the value is set to ERROR_VALUE.
 * @param error_ptr Pointer to a uint8_t variable where the error status will be stored.
 *                  Must not be NULL. 0 - no error, otherwise - error code.
 *                  Error codes: 
 *                   - CMD_FAIL_ERROR - read operation failed, 
 *                   - LOW_VOLTAGE_ERROR - low voltage error
 * 
 * @ingroup eeprom
 */
#define eeprom_read_byte(addr_high, addr_low, value_ptr, error_ptr)     \
do {                                                                    \
    if (power_low_voltage_flag_get())                                  \
    {                                                                   \
        *error_ptr = LOW_VOLTAGE_ERROR;                                 \
        *value_ptr = ERROR_VALUE;                                       \
        power_low_voltage_flag_clear();                                 \
    }                                                                   \
    else                                                                \
    {                                                                   \
        /* Enable IAP */                                                \
        bit_set(IAP_CONTR, SBIT7);                                      \
        /* Set IAP WT2 WT1 WT0 to 011 for eeprom read waiting */        \
        IAP_CONTR &= ~0x07;                                             \
        IAP_CONTR |= 0x03;                                              \
                                                                        \
        /* Set address */                                               \
        IAP_ADDRH = (addr_high);                                        \
        IAP_ADDRL = (addr_low);                                         \
                                                                        \
        /* Set read operation */                                        \
        IAP_CMD = REAP_OP;                                              \
                                                                        \
        /* Set start read sequence */                                   \
        IAP_TRIG = READ_OP_TRIGGER_SEQ_FIRST_BYTE;                      \
        IAP_TRIG = READ_OP_TRIGGER_SEQ_SECOND_BYTE;                     \
                                                                        \
        /* Read error status from IAP */                                \
        *error_ptr = get_bit(IAP_CONTR, CMD_FAIL_BIT);                  \
        /* if no operation error read data from IAP otherwise value is ERROR_VALUE */ \
        *value_ptr = *error_ptr != CMD_SUCCESS ? ERROR_VALUE : IAP_DATA;\
                                                                        \
        /* Disable IAP */                                               \
        bit_clr(IAP_CONTR, CBIT7);                                      \
    }                                                                   \
} while (0)

#endif
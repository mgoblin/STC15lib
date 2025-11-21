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
#include <power_management.h>


/**
 * @brief EEPROM operation types
 * 
 * @ingroup eeprom
 */
enum eeprom_operation_t
{
    /** @brief Read operation */
    READ_OP = 0x01,
    /** @brief Write operation */
    WRITE_OP = 0x02,
    /** @brief Erase operation */
    ERASE_OP = 0x03,
};

/**
 * @brief EEPROM operation status
 * 
 * @ingroup eeprom
 */
enum eeprom_operation_status_t
{
    /** @brief Operation success */
    CMD_SUCCESS = 0,
    /** @brief Operation fail */
    CMD_FAIL_ERROR = 1,
    /** @brief Low voltage error */
    LOW_VOLTAGE_ERROR = 2,
};


/**
 * @brief Read operation trigger sequence first byte
 * 
 * @ingroup eeprom
 */
#define OP_TRIGGER_SEQ_FIRST_BYTE 0x5A
/**
 * @brief Read operation trigger sequence second byte
 * 
 * @ingroup eeprom
 */
#define OP_TRIGGER_SEQ_SECOND_BYTE 0xA5

/**
 * @brief Command fail error code
 * 
 * @ingroup eeprom
 */
#define CMD_FAIL_BIT 4

/**
 * @brief Error value
 * 
 * @ingroup eeprom
 */
#define ERROR_VALUE 0xFF

/**
 * @brief Disables IAP
 * 
 * @details This function disables EEPROM operation via IAP
 * registers and clear it.
 * 
 * @ingroup eeprom
 */
#define eeprom_disable_iap()                    \
do {                                            \
        /* Disable IAP */                       \
        bit_clr(IAP_CONTR, CBIT7);              \
        IAP_CMD = 0x00;                         \
        IAP_TRIG = 0x00;                        \
        IAP_ADDRH = 0xFF;                       \
        IAP_ADDRL = 0xFF;                       \
} while(0)

/**
 * @brief get last operation result
 * 
 * @details Last operation result is stored in IAP_CONTR register and dont 
 * changed on low voltage error
 * 
 * @ingroup eeprom
 */
#define get_eeprom_last_operation_result() (get_bit(IAP_CONTR, CMD_FAIL_BIT) ? CMD_FAIL_ERROR : CMD_SUCCESS)    

/**
 * @brief Reads single byte from the EEPROM at the given address
 * 
 * This function performs a read operation from the EEPROM using the provided
 * high and low bytes of the address. The data read from the EEPROM is stored 
 * in the location pointed to by 'value_ptr'. 
 * For reading from the EEPROM IAP registers are used.
 *
 * @param addr_high uint8_t High byte of the EEPROM address to read from.
 * @param addr_low  uint8_t Low byte of the EEPROM address to read from.
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
    if (power_low_voltage_flag_get())                                   \
    {                                                                   \
        *error_ptr = LOW_VOLTAGE_ERROR;                                 \
        *value_ptr = ERROR_VALUE;                                       \
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
        IAP_CMD = READ_OP;                                              \
                                                                        \
        /* Set start operation sequence */                              \
        IAP_TRIG = OP_TRIGGER_SEQ_FIRST_BYTE;                           \
        IAP_TRIG = OP_TRIGGER_SEQ_SECOND_BYTE;                          \
                                                                        \
        /* Wait for operation to complete */                            \
        NOP();                                                          \
                                                                        \
        /* Read error status from IAP */                                \
        *error_ptr = get_eeprom_last_operation_result();                \
        /* if no operation error read data from IAP otherwise value is ERROR_VALUE */ \
        *value_ptr = (*error_ptr) ? ERROR_VALUE : IAP_DATA;             \
                                                                        \
        eeprom_disable_iap();                                           \
    }                                                                   \
} while (0)

/**
 * @brief Erases a sector in the EEPROM starting from a specified address.
 *
 * This function performs an erase operation on a 512 bytes sector of the EEPROM memory.
 * The sector is identified by its starting address. 
 * The function updates the error status via the provided error pointer.
 *
 * @param sector_start_addr uint8_t The starting address of the EEPROM sector to be erased.
 *                          Must be a valid sector start address.
 * @param error_ptr         Pointer to a uint8_t variable where the error status will be stored.
 *                          Must not be NULL. 0 - no error, otherwise - error code.
 *                          Error codes: 
 *                              - CMD_FAIL_ERROR - read operation failed, 
 *                              - LOW_VOLTAGE_ERROR - low voltage error
 *
 * @warning This function modifies EEPROM contents; ensure data integrity requirements
 *          are met before calling it.
 * 
 * @ingroup eeprom
 */
#define eeprom_erase_page(sector_start_addr, error_ptr)         \
do {                                                            \
    if (power_low_voltage_flag_get())                           \
    {                                                           \
        *error_ptr = LOW_VOLTAGE_ERROR;                         \
    }                                                           \
    else                                                        \
    {                                                           \
        /* Set address */                                       \
        IAP_ADDRH = (sector_start_addr);                        \
        IAP_ADDRL = 0x00;                                       \
                                                                \
        /* Set erase operation waiting */                       \
        IAP_CONTR &= ~0x07;                                     \
        IAP_CONTR |= 0x03;                                      \
                                                                \
        /* Enable IAP */                                        \
        bit_set(IAP_CONTR, SBIT7);                              \
                                                                \
        /* Set erase operation */                               \
        IAP_CMD = ERASE_OP;                                     \
                                                                \
        /* Set start operation sequence */                      \
        IAP_TRIG = OP_TRIGGER_SEQ_FIRST_BYTE;                   \
        IAP_TRIG = OP_TRIGGER_SEQ_SECOND_BYTE;                  \
                                                                \
        /* Wait for operation to complete */                    \
        NOP();                                                  \
                                                                \
        /* Read error status from IAP */                        \
        *error_ptr = get_eeprom_last_operation_result();        \
                                                                \
        eeprom_disable_iap();                                   \
    }                                                           \
} while(0)

/**
 * @brief Writes a single byte to the EEPROM at the specified address.
 *
 * This function performs a byte write operation to the EEPROM memory using the given
 * high and low bytes of the address. The value to be written is passed as an argument,
 * and any error condition encountered during the operation is reported via the error pointer.
 *
 * @param addr_high uint8_t  High byte of the EEPROM address (bits 15-8).
 * @param addr_low  uint8_t  Low byte of the EEPROM address (bits 7-0).
 * @param value     uint8_t  The byte value to be written to EEPROM.
 * @param error_ptr uint8_t* Pointer to a uint8_t variable where the error status will be stored:
 *                           Must not be NULL. 0 - no error, otherwise - error code.
 *                           Error codes: 
 *                              - CMD_FAIL_ERROR - read operation failed, 
 *                              - LOW_VOLTAGE_ERROR - low voltage error
 * 
 * @note This is an inline function, intended for fast, low-level EEPROM access.
 *       Ensure that the EEPROM is ready for writing prior to calling this function.
 *       Improper use may result in data corruption or missed writes.
 * 
 * @warning Before write byte EEPORM page must be erased.
 *
 * @warning This function does not perform address bounds checking.
 *          It is the caller's responsibility to ensure valid EEPROM addresses.
 * 
 * @ingroup eeprom
 */
void eeprom_write_byte(uint8_t addr_high, uint8_t addr_low, uint8_t value, uint8_t *error_ptr);

#endif
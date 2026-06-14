/**
 * @file mem_dump.c
 * @brief Dump IDATA and XDATA memory contents to UART
 *
 * Dumps the first 256 bytes of IDATA (internal RAM) and
 * the first 256 bytes of XDATA (external RAM) to UART1
 * at 115200 baud.
 *
 * Output format is a standard hex dump with 16 bytes per row,
 * showing offset addresses and byte values in hexadecimal.
 */

#include "mem_print.h"

/** @brief Starting address for IDATA dump */
#define IDATA_DUMP_ADDR 0x00
/** @brief Number of bytes to dump from IDATA */
#define IDATA_DUMP_SIZE 256

/** @brief Starting address for XDATA dump */
#define XDATA_DUMP_ADDR 0x00
/** @brief Number of bytes to dump from XDATA */
#define XDATA_DUMP_SIZE 256

/** @brief Number of bytes per output row */
#define ROW_LENGTH 16

/** @brief UART baud rate for serial output */
#define UART_BAUD_RATE 115200

/**
 * @brief Print IDATA memory contents in hex dump format
 *
 * Reads and prints @ref IDATA_DUMP_SIZE bytes starting from
 * @ref IDATA_DUMP_ADDR in the IDATA address space.
 */
static void print_idata(void)
{
    uint8_t address = IDATA_DUMP_ADDR;
    
    printf_tiny("IDATA:\r\n");
    print_header_row();

    for (uint8_t row = 0; row < IDATA_DUMP_SIZE / ROW_LENGTH; row++)
    {
        print_row_offset(address);
        
        for (uint8_t column = 0; column < ROW_LENGTH; column++)
        {
            uint8_t data = *((__idata uint8_t *) address);
            print_byte_value(data);
            address++;
        }
        print_row_end();
    }

    print_footer_row();
}

/**
 * @brief Print XDATA memory contents in hex dump format
 *
 * Reads and prints @ref XDATA_DUMP_SIZE bytes starting from
 * @ref XDATA_DUMP_ADDR in the XDATA address space.
 */
static void print_xdata(void)
{
    uint8_t address = XDATA_DUMP_ADDR;
    printf_tiny("XDATA:\r\n");
    print_header_row();

    for (uint8_t row = 0; row < XDATA_DUMP_SIZE / ROW_LENGTH; row++)
    {
        print_row_offset(address);

        for (uint8_t column = 0; column < ROW_LENGTH; column++)
        {
            uint8_t data = *((__xdata uint8_t *) address);
            print_byte_value(data);
            address++;
        }

        print_row_end();
    }

    print_footer_row();
}
/**
 * Entry point
 */
void main(void)
{
    uart1_init(UART_BAUD_RATE);
    
    while (1)
    {
        print_idata();
        printf_tiny("\r\n");
        print_xdata();
        printf_tiny("\r\n");
    }
}

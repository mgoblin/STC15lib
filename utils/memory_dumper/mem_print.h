/**
 * @file mem_print.h
 * @brief Hex dump formatting functions for memory dumper utility
 *
 * Provides functions to print formatted hex dump output to UART,
 * including header/footer rows, offset addresses, and byte values.
 */
#pragma once

#include <stdint.h>
#include <stdio.h>
#include <uart.h>

/**
 * @brief Print the header row (column indices 0-F)
 */
void print_header_row(void);

/**
 * @brief Print the footer row (same as header)
 */
void print_footer_row(void);

/**
 * @brief Print the row offset address in hex
 * @param address Offset address to print (e.g. 0x00, 0x10, ... 0xF0)
 */
void print_row_offset(uint8_t address);

/**
 * @brief Print the end-of-row marker
 */
void print_row_end(void);

/**
 * @brief Print a single byte value in hex with leading pipe
 * @param byte Byte value to print
 */
void print_byte_value(uint8_t byte);

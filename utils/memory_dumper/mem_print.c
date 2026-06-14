/**
 * @file mem_print.c
 * @brief Hex dump formatting functions for memory dumper utility
 */
#include "mem_print.h"

/** @brief Header/footer string displayed at top and bottom of each dump */
static __code const char hf_str[] = "    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n";

void print_header_row(void)
{
    printf_tiny(hf_str);
}

void print_footer_row(void)
{
    printf_tiny(hf_str);
}

void print_row_offset(uint8_t address)
{
    if (address < 0x10)
    {
        printf_tiny("0%x ", address);
    }
    else
    {
        printf_tiny("%x ", address);
    }
}

void print_row_end(void)
{
    printf_tiny("|\r\n");
}

void print_byte_value(uint8_t byte)
{
    if (byte < 0x10)
    {
        printf_tiny("|0%x", byte);
    }
    else
    {
        printf_tiny("|%x", byte);
    }
}
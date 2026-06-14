#include <stdint.h>

#include <stdio.h>
#include <uart.h>

void print_header_row(void);
void print_footer_row(void);

void print_row_offset(uint8_t address);

void print_row_end();

void print_byte_value(uint8_t byte);

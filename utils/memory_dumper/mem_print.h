#include <stdio.h>
#include <uart.h>

#define print_header_row() (printf_tiny("    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n"))
#define print_footer_row() (printf_tiny("    0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n"))
#define print_hex_byte(val, m1, m2) (val < 0x10 ? printf_tiny(m1, val) : printf_tiny(m2, val))
#define print_row_offset(val) (print_hex_byte((val), "0%x ", "%x "))
#define print_byte_value(val) (print_hex_byte((val), "|0%x", "|%x"))
#define print_row_end() (printf_tiny("|\r\n"))
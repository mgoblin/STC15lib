/** 
 *  Bit manipulation example.
 *  
 *  bit_shift_left, bit_shift_right, bit_mask used for bit manipulation on initial byte value
 * 
 *  printf_tiny send results via UART. You can use printf also, but it need more flash
 */
// for uint8_t
#include <stdint.h>

// include bit manipulation macroses
#include <bits.h>

// include uart and print routines
#include <uart.h>
#include <stdio.h>

// include for delay_ms
#include <delay.h>

// define macro doesnt allocate memory or code space
#define original_byte 0b10000001  

// allocate byte MCU flash. It cannot be modified and use as a constant value
__code uint8_t shifted_left_byte = bit_shift_left(original_byte, 1);

// allocate byte in MCU RAM. This value not modifiable because have declared as const
__data const uint8_t shifted_right_byte = bit_shift_right(original_byte, 1);

// allocate byte in MCU RAM for modifiable variable
uint8_t bit_mask_2 = bit_mask(2);

void main()
{
    uart1_init(9600);
    while(1)
    {
        printf_tiny("original_byte = 0x%x\n", original_byte);
        printf_tiny("bit_shift_left(original_byte, 1) = 0x%x\n", shifted_left_byte);
        printf_tiny("bit_shift_right(original_byte, 1) = 0x%x\n", shifted_right_byte);
        printf_tiny("bit_mask(2) = 0x%x\n", bit_mask_2);

        delay_ms(1000);
    }
}
#include <stdio.h>

#include <sys.h>
#include <bits.h>
#include <uart.h>
#include <delay.h>

void main()
{
    unsigned char original_byte = 0b10000001;
    unsigned char shifted_left_byte = bit_shift_left(original_byte, 1);
    unsigned char shifted_right_byte = bit_shift_right(original_byte, 1);

    unsigned char bit_mask_2 = bit_mask(2);

    uart_init(9600);
    printf("original_byte = %i\n", original_byte);
    printf("bit_shift_left(original_byte, 1) = %i\n", shifted_left_byte);
    printf("bit_shift_right(original_byte, 1) = %i\n", shifted_right_byte);
    printf("bit_mask(2) = %i\n", bit_mask_2);
    delay_ms(1000);
}
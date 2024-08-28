#include <stdio.h>

#include <sys/sys.h>
#include <sys/bits.h>
#include <uart/uart.h>
#include <delay/delay.h>

void main()
{
    unsigned char byte1 = 0x01;
    unsigned char byte2 = bit_shift_left(byte1, 1);

    uart_init();
    printf("byte1 = %d, byte2 = %d\n", byte1, byte2);
    delay_ms(1000);
}
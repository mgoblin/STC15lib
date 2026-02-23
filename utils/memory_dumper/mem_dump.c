/**
 * Dump memory from 0x00 to 0xFF to UART
 * 
 * UART baud rate is 115200 
 */
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <uart.h>


#define START_DUMP_ADDR 0x00
#define DUMP_SIZE 256

#define ROW_LENGTH 16

/** Dont clear memory */
void _mcs51_genRAMCLEAR() {}

void hex_to_string(uint8_t hex, char str_buffer[3])
{
    
    __itoa(hex, str_buffer, 16);
    if (hex < 0x10)
    {
        str_buffer[1] = str_buffer[0];
        str_buffer[0] = '0';
    }
    str_buffer[2] = 0;
}

void main()
{
    uart1_init(115200);

    const uint8_t row_count = DUMP_SIZE / ROW_LENGTH;

    while(1)
    {
        uint8_t address = START_DUMP_ADDR;
        char str_buffer[3];

        // print dump header
        printf_tiny("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");

        for(uint8_t row = 0; row < row_count; row++)
        {
            hex_to_string(address, str_buffer);
            printf_tiny("0x%s ", str_buffer);
            for(uint8_t column = 0; column < ROW_LENGTH; column++)
            {
                __idata uint8_t *data_address;
                data_address = (__idata uint8_t *) address;
                hex_to_string(*data_address, str_buffer);
                printf_tiny("|");
                printf_tiny("%s", str_buffer);
                address++;
            }
            printf_tiny("|\r\n");
        }

        // print dump footer
        printf_tiny("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");
    }
} 
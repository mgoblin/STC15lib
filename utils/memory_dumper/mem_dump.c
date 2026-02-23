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

void main()
{
    uart1_init(115200);

    const uint8_t row_count = DUMP_SIZE / ROW_LENGTH;

    while(1)
    {
        uint8_t address = START_DUMP_ADDR;

        // print dump header row
        printf_tiny("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");

        for(uint8_t row = 0; row < row_count; row++)
        {
            address < 0x10 ? 
                printf_tiny("0x0%x", address) : printf_tiny("0x%x", address);
            
            for(uint8_t column = 0; column < ROW_LENGTH; column++)
            {
                __idata uint8_t *data_address;
                data_address = (__idata uint8_t *) address;
                *data_address < 0x10 ?
                    printf_tiny("|0%x", *data_address): printf_tiny("|%x", *data_address);
                address++;
            }

            printf_tiny("|\r\n");
        }

        // print dump footer row
        printf_tiny("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\r\n");
    }
} 
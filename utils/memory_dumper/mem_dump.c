/**
 * Dump memory from 0x00 to 0xFF to UART
 * 
 * UART baud rate is 115200 
 */
#include "mem_print.h"

#define START_DUMP_ADDR 0x00
#define DUMP_SIZE 256

#define ROW_LENGTH 16

void main()
{
    uart1_init(115200);

    while(1)
    {
        uint8_t address = START_DUMP_ADDR;

        // print dump header row
        print_header_row();

        for(uint8_t row = 0; row < DUMP_SIZE / ROW_LENGTH; row++)
        {
            print_row_offset(address);
            
            for(uint8_t column = 0; column < ROW_LENGTH; column++)
            {
                print_byte_value(*((__idata uint8_t *) address));
                address++;
            }
            print_row_end();
        }

        // print dump footer row
        print_footer_row();
    }
} 
#include <stdint.h>
#include <stdlib.h>

#include <STC15Fxx.h>

#define START_DUMP_ADDR 0x00
#define DUMP_SIZE 256

#define ROW_LENGTH 16

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

void print_str(char *str)
{
    while (*str != 0)
    {
        // uart1_send_byte(*str);
        SBUF = *str;
	    while(TI==0);
	    TI=0;
        str++;
    }
}

void main()
{
    // uart1_init(115200);
    T2H = 0xFF;
    T2L = 0xE7;
    SCON = 0x50;
    AUXR |= 0x15;

    const uint8_t row_count = DUMP_SIZE / ROW_LENGTH;

    while(1)
    {
        uint8_t address = START_DUMP_ADDR;
        char str_buffer[3];

        // print dump header
        print_str("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");

        for(uint8_t row = 0; row < row_count; row++)
        {
            hex_to_string(address, str_buffer);
            print_str("0x");
            print_str(str_buffer);
            print_str(" ");
            for(uint8_t column = 0; column < ROW_LENGTH; column++)
            {
                __idata uint8_t *data_address;
                data_address = (__idata uint8_t *) address;
                hex_to_string(*data_address, str_buffer);
                print_str("|");
                print_str(str_buffer);
                address++;
            }
            print_str("|\n");
        }

        // print dump footer
        print_str("      0  1  2  3  4  5  6  7  8  9  A  B  C  D  E  F\n");
    }
} 
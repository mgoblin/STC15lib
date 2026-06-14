/**
 * Dump memory from 0x00 to 0xFF to UART
 * 
 * UART baud rate is 115200 
 */
#include "mem_print.h"

#define IDATA_DUMP_ADDR 0x00
#define IDATA_DUMP_SIZE 256

#define XDATA_DUMP_ADDR 0x00
#define XDATA_DUMP_SIZE 256

#define ROW_LENGTH 16

#define UART_BAUD_RATE 115200

void print_idata(void)
{
    uint8_t address = IDATA_DUMP_ADDR;
    
    printf_tiny("IDATA:\r\n");
    
    // print dump header row
    print_header_row();

    for(uint8_t row = 0; row < IDATA_DUMP_SIZE / ROW_LENGTH; row++)
    {
        print_row_offset(address);
        
        for(uint8_t column = 0; column < ROW_LENGTH; column++)
        {
            uint8_t data = *((__idata uint8_t *) address);
            print_byte_value(data);
            address++;
        }
        print_row_end();
    }

    // print dump footer row
    print_footer_row();
}

void print_xdata(void)
{
    uint8_t address = XDATA_DUMP_ADDR;
    printf_tiny("XDATA:\r\n");

    print_header_row();

    for(uint8_t row = 0; row < XDATA_DUMP_SIZE / ROW_LENGTH; row++)
    {
        print_row_offset(address); 

        for(uint8_t column = 0; column < ROW_LENGTH; column++)
        {
            uint8_t data = *((__xdata uint8_t *) address); 
            print_byte_value(data);
            address++;
        }

        print_row_end();
    }

    print_footer_row();
}

void main()
{
    uart1_init(UART_BAUD_RATE);

    while(1)
    {
        print_idata();
        printf_tiny("\r\n");
        print_xdata();
        printf_tiny("\r\n");
    }
} 

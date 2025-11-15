#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

volatile uint8_t byte = 0;
volatile uint8_t has_error = 0;

void main(void) 
{
    uart1_init(9600);

    uint8_t addr_high = 0x00;

    while (1)
    {
        // Read byte from EEPROM at addresses 0x00000-0x0002 via IAP
        for(uint8_t addr_low = 0; addr_low < 3; addr_low++)
        {
            eeprom_read_byte(addr_high, addr_low, &byte, &has_error);
            if (!has_error)
            {
                printf_tiny("Byte on address %x %x is %x\r\n", addr_high, addr_low, byte);
            }
            else
            {
                printf_tiny("Error reading byte on address %x %x\r\n", addr_high, addr_low);
            }   
        }
    }
}
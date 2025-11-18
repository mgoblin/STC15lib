/** 
 * This example deomstrate how to read  bytes from EEPROM using IAP registers.
 * 
 * Before executing this example, make sure that the EEPROM is programmed.
 * Example read and print the first READ_BYTES_COUNT (5) bytes from EEPROM.
 */

#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#define READ_BYTES_COUNT 5

// eeprom readed byte variable
volatile uint8_t byte = 0;
// eeprom error flag variable
volatile uint8_t has_error = 0;

const uint8_t add_high = 0x00;

void main(void) 
{
    uart1_init(9600);

    power_low_voltage_flag_clear();

    while (1)
    {
        // Read byte from EEPROM at addresses 0x00000-0x0002 via IAP
        for(uint8_t addr_low = 0; addr_low < READ_BYTES_COUNT; addr_low++)
        {
            eeprom_read_byte(add_high, addr_low, &byte, &has_error);
            if (!has_error)
            {
                printf_tiny("Byte on address %x %x is %x\r\n", add_high, addr_low, byte);
            }
            else
            {
                printf_tiny("Error reading byte on address %x %x\r\n", add_high, addr_low);
            }   
        }
    }
}
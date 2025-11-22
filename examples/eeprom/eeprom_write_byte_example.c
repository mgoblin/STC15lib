/**
 * This example demonstrates how to write byte to EEPROM.
 * 
 * On successful write, byte is read back and printed.
 */
#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define ADDR_H 0x00
#define ADDR_L 0x00

#define EMPTY_VALUE 0x00
#define DEFAULT_ERROR 0x00
#define DEFAULT_VALUE 0x55

#define DELAY_MS 1000

uint8_t error = DEFAULT_ERROR;
uint8_t value = EMPTY_VALUE;

void main(void)
{
    uart1_init(9600);
    power_low_voltage_flag_clear();

    while (1)
    {
        // Before writing, page will be erased
        eeprom_erase_page(ADDR_H, &error);
        eeprom_write_byte(ADDR_H, ADDR_L, DEFAULT_VALUE, &error);
        
        if (!error)
        {
            printf_tiny("Write to %x %x = %x successful\r\n", ADDR_H, ADDR_L, DEFAULT_VALUE);
            // Read back
            eeprom_read_byte(ADDR_H, ADDR_L, &value, &error);
            printf_tiny("Read back %x with status %x\r\n\r\n", value, error);
        }
        else
        {
            printf_tiny("Write to %x %x failed\r\n\r\n", ADDR_H, ADDR_L);
        }

        delay_ms(DELAY_MS);
    }
    
}
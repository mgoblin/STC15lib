#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define ADDR_H 0x00
#define ADDR_L 0x00

#define DEFAULT_VALUE 0x00
#define DEFAULT_ERROR 0x00

#define DELAY_MS 1000

void main(void)
{
    uint8_t error = DEFAULT_ERROR;
    uint8_t value = DEFAULT_VALUE;

    uart1_init(9600);
    power_low_voltage_flag_clear();

    while (1)
    {
        eeprom_erase_page(ADDR_H, &error);
        printf_tiny("Erase page %x and status %x\r\n", ADDR_H, error);
        
        value = 0x55;
        eeprom_write_byte(ADDR_H, ADDR_L, value, &error);
        
        if (!error)
        {
            printf_tiny("Wrire to %x %x value %x successful\r\n", ADDR_H, ADDR_L, value);
            // Read back
            value = 0;
            eeprom_read_byte(ADDR_H, ADDR_L, &value, &error);
            printf_tiny("Read back from %x %x = %x and status %x\r\n", ADDR_H, ADDR_L, value, error);
        }
        else
        {
            printf_tiny("Wrire to %x %x failed\r\n", ADDR_H, ADDR_L);
        }

        printf_tiny("\r\n\r\n");

        delay_ms(DELAY_MS);
    }
    
}
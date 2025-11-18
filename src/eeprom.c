#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#define SECTOR_START_ADDR 0x00


volatile uint8_t eeprom_operation_error;

void main(void)
{
    uart1_init(9600);

    power_low_voltage_flag_clear();

    while (1)
    {
        eeprom_erase_sector(SECTOR_START_ADDR, &eeprom_operation_error);
        if (!eeprom_operation_error)
        {
            printf_tiny("512-bytes sector at address %x %x erased\r\n", SECTOR_START_ADDR, 0x00);
        }
        else
        {
            printf_tiny("512-bytes sector at address %x %x erase error\r\n", SECTOR_START_ADDR, 0x00);
        }
    }
    
}
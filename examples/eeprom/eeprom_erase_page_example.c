/** 
 * This example demonstrates how to erase 512-bytes page of EEPROM.
 * 
 * For the test purpose first page with start address 0x00 is erased every 3 seconds.
 * 
 * Please be careful with this example. 
 * EEPROM has limited amount of erase cycles.
 */
#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define LED P10

#define EEPROM_TEST_SECTOR_ADDR 0x00


void main(void)
{
    uart1_init(9600);

    power_low_voltage_flag_clear();
    
    uint8_t eeprom_operation_error;

    while (1)
    {
        eeprom_erase_page(EEPROM_TEST_SECTOR_ADDR, &eeprom_operation_error);
        if (!eeprom_operation_error)
        {
            printf_tiny("512-bytes sector at address %x erased\r\n", EEPROM_TEST_SECTOR_ADDR);
        }
        else
        {
            printf_tiny("512-bytes sector at address %x erase error\r\n", EEPROM_TEST_SECTOR_ADDR);
        }
        
        LED = !LED;
        delay_ms(3000);
    }
    
}
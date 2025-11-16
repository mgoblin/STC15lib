#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

void eeprom_erase_sector(uint8_t addr_high, uint8_t addr_low)
{
    return;
}

void main(void)
{
    uart1_init(9600);

    while (1)
    {
        eeprom_erase_sector(0x00, 0x00);
        printf_tiny("512-bytes sector at address %x %x erased\r\n", 0x00, 0x00);

        delay_ms(1000);
    }
    
}
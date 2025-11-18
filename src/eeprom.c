#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define SECTOR_START_ADDR 0x00

void eeprom_erase_sector(uint8_t sector_start_addr, uint8_t* error_ptr)
{
    if (power_low_voltage_flag_get())
    {
        *error_ptr = LOW_VOLTAGE_ERROR;
    }
    else
    {
        /* Set address */
        IAP_ADDRH = sector_start_addr;
        IAP_ADDRL = 0x00;

        /* Set erase operation waiting */
        IAP_CONTR &= ~0x07;
        IAP_CONTR |= 0x03;
        
        /* Enable IAP */
        bit_set(IAP_CONTR, SBIT7);

        /* Set erase operation */
        IAP_CMD = ERASE_OP;

        /* Set start operation sequence */
        IAP_TRIG = OP_TRIGGER_SEQ_FIRST_BYTE;
        IAP_TRIG = OP_TRIGGER_SEQ_SECOND_BYTE;

        /* Wait for operation to complete */
        NOP();

        delay_ms(1000);

        /* Read error status from IAP */
        *error_ptr = get_bit(IAP_CONTR, CMD_FAIL_BIT);

        /* Disable IAP */
        bit_clr(IAP_CONTR, CBIT7);
        IAP_CMD = 0x00;
        IAP_TRIG = 0x00;
        IAP_ADDRH = 0xFF;
        IAP_ADDRL = 0xFF;
    }
}

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
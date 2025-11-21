#include <eeprom.h>

#include <uart.h>
#include <stdio.h>

#include <delay.h>

#define ADDR_H 0x00
#define ADDR_L 0x00

static inline void eeprom_write_byte(uint8_t addr_high, uint8_t addr_low, uint8_t value, uint8_t *error_ptr)
{
    if (power_low_voltage_flag_get())
    {
        *error_ptr = LOW_VOLTAGE_ERROR;
    }
    else
    {
        /* Set address */
        IAP_ADDRH = addr_high;
        IAP_ADDRL = addr_low;

        /* Set write operation waiting */
        IAP_CONTR &= ~0x07;
        IAP_CONTR |= 0x03;

        /* Enable IAP */
        bit_set(IAP_CONTR, SBIT7);

        /* Set write operation */
        IAP_CMD = WRITE_OP;

        /* Set data */
        IAP_DATA = value;

        /* Set start operation sequence */
        IAP_TRIG = OP_TRIGGER_SEQ_FIRST_BYTE;
        IAP_TRIG = OP_TRIGGER_SEQ_SECOND_BYTE;

        /* Wait for operation to complete */
        NOP();

        /* Read error status from IAP */
        *error_ptr = get_eeprom_last_operation_result();
        
        eeprom_disable_iap();
    }
}
void main(void)
{
    uint8_t error = 0;
    uint8_t value = 0;

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

        delay_ms(1000);
    }
    
}
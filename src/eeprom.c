#include <eeprom.h>

#include <bits.h>

#include <uart.h>
#include <stdio.h>

void eeprom_read_byte(
    uint8_t addr_high, 
    uint8_t addr_low, 
    uint8_t* value_ptr, 
    uint8_t* error_ptr
)
{
    // Enable IAP
    bit_set(IAP_CONTR, SBIT7);

    // Addresses readed via IAP from 0000h to 13FFh
    // Addresses readed via MOVC from 2000h to 33FFh
    IAP_ADDRH = addr_high;
    IAP_ADDRL = addr_low;
    IAP_CMD = REAP_OP; // Read

    // Start IAP first sequence byte
    IAP_TRIG = READ_OP_TRIGGER_SEQ_FIRST_BYTE; 
    // Start IAP second sequence byte
    IAP_TRIG = READ_OP_TRIGGER_SEQ_SECOND_BYTE; 

    // Wait for IAP finish
    NOP();
    NOP();
    NOP();

    // Read data from IAP
    *value_ptr = IAP_DATA;
    // Read error status from IAP
    *error_ptr = get_bit(IAP_CONTR, 4);

    // Disable IAP
    bit_clr(IAP_CONTR, CBIT7);
}

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
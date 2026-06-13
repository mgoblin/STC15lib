/**
 * This example demonstrates how to write data arrya into the EEPROM page.
 * 
 * data[] array contains 10 bytes. 
 * Data array is written into the EEPROM page on firmware start.
 * 
 * LED is light on when writing is starting and off when write 
 * is successfully completed.
 * 
 * After writing, data is cyclycally read back and compared with original data.
 * 
 * If the read value matches the written value, the LED blinks.
 * If error occurs thenLED will be always on.
 */
#include <eeprom.h>

#include <delay.h>


// LED definitions
#define LED P10
#define LED_ON 0
#define LED_OFF 1

// EEPROM page address
#define ADDR_H 0x00

// Data array for writing
const uint8_t data[] = { 9, 8, 7, 6, 5, 4, 2, 2, 1, 0 };
#define DATA_SIZE 10


void main(void)
{
    // LED on and start writing
    LED = LED_OFF;

    clear_power_low_voltage_flag();

    eeprom_operation_status_t error = CMD_SUCCESS;
    eeprom_write_page(ADDR_H, data, DATA_SIZE, &error);

    if (error != CMD_SUCCESS)
    {
        return;
    }

    LED = LED_ON;
    delay_ms(5000);

    // LED off on success
    LED = LED_OFF;

    while (1)
    {
        for (uint8_t i = 0; i < DATA_SIZE; i++)
        {
            uint8_t value = 0x00;

            eeprom_read_byte(ADDR_H, i, &value, &error);
            if (error != CMD_SUCCESS || data[i] != value )
            {
                LED = LED_ON;
                break;
            }
            else{
                LED = !LED;
                delay_ms(500);
            }
        }
    }
}
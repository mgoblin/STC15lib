#include <uart.h>
#include <chip_id.h>
#include <stdio.h>

void main()
{
    uart_init(9600);

    uint8_t *id = get_chipid();

    while (1)
    {
        printf_tiny("Chip id is ");
        for (uint8_t i = 0; i < ID_SIZE; i++)
        {
            printf_tiny("%x", id[i]);
        }
        printf_tiny("\n");
    }
    
}
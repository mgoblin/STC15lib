#include <chip_id.h>

#include <stdio.h>
#include <uart.h>

void main()
{
    uart1_init(9600);

    while (1)
    {
        const uint8_t *cid2 = &chip_id;
        for(uint8_t i = 0; i < CHIP_ID_SIZE; i++)
        {
            printf_tiny("%x", cid2[i]);
        }
        printf_tiny("\n");
    }
    
}
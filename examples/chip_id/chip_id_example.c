/** 
 * How to get chip id
 */
#include <chip_id.h>

#include <stdio.h>
#include <uart.h>

const uint8_t *cid2 = &chip_id;
uint8_t cid[CHIP_ID_SIZE];

void print_chip_id(const uint8_t *chip_id)
{
    for(uint8_t i = 0; i < CHIP_ID_SIZE; i++)
    {
        printf_tiny("%x", chip_id[i]);
    }
    printf_tiny("\n");
}

void main()
{
    uart1_init(9600);

    get_chipid(cid);

    while (1)
    {
        printf_tiny("   chip_id bytes: ");
        print_chip_id(cid2);

        printf_tiny("get_chipid bytes: ");
        print_chip_id(cid);
    }
    
}
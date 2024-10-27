#include <chip_id.h>

#define ID_ADDR_RAM 0x1ff9

volatile __code __at(ID_ADDR_RAM) uint8_t chip_id;

uint8_t* get_chipid() 
{
    uint8_t id[ID_SIZE] = { 0, 0, 0, 0, 0, 0, 0 };
    const uint8_t *idptr = &chip_id;

    for (uint8_t i = 0; i < ID_SIZE; i++) 
    {
        id[i] = *idptr; 
        idptr++;
    }
    return id;    
}
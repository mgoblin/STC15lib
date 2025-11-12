#ifndef STC15_EEPROMH
#define STC15_EEPROMH

#include <stdint.h>

#include <sys.h>

uint8_t eeprom_read(uint8_t addr_high, uint8_t addr_low, uint8_t* value_ptr);

#endif
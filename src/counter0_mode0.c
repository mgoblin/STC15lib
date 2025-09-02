#include <counter0_mode0.h>

void counter0_mode0_set_value(uint16_t value)
{
    TH0 = (uint8_t)(value >> 8);
    TL0 = (uint8_t)(value & 0xff);
}

uint16_t counter0_mode0_get_value()
{
    return (((uint16_t) TH0) << 8) | TL0;
}

bool is_counter0_mode0_started()
{
    return TR0 == 1;
}
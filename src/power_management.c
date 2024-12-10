#include <power_management.h>

void wakeup_timer_init(uint16_t ticks)
{
    uint16_t value = 32768 - (ticks & 0x7fff);
    WKTCH = value >> 8;
    WKTCL = value & 0xff;
}

void wakeup_timer_start()
{
    bit_set(WKTCH, SBIT7);
}

void wakeup_timer_stop()
{
    bit_clr(WKTCH, CBIT7);
}

bool is_wakeup_timer_started()
{
    return test_if_bit_set(WKTCH, SBIT7);
}
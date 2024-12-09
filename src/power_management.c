#include <power_management.h>

void wakeup_timer_init(uint16_t ticks)
{
    WKTCH = (ticks >> 8) & 0x7f;
    WKTCL = 0x01;
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
    return test_if_any_bit_set(WKTCH, SBIT7);
}
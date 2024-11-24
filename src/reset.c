#include <reset.h>

void wdt_init(uint8_t wdt_scale)
{
    WDT_CONTR &= 0x00;
    WDT_CONTR |= (wdt_scale & 0x07);
}

void wdt_start()
{
    bit_set(WDT_CONTR, 5);
}

void wdt_stop()
{
    bit_clr(WDT_CONTR, 5);
}

bool is_wdt_started()
{
    return test_if_bit_set(WDT_CONTR, 5);
}

void wdt_reset()
{
    bit_set(WDT_CONTR, 4);
}

bool is_wdt_flag_on()
{
    return test_if_bit_set(WDT_CONTR, 7);
}

void reset_wdt_flag()
{
    bit_clr(WDT_CONTR, 7);
}
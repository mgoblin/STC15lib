#include <reset.h>

bool is_wdt_flag_on()
{
    return test_if_bit_set(WDT_CONTR, 7);
}

void reset_wdt_flag()
{
    bit_clr(WDT_CONTR, 7);
}
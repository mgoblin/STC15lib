#include <sys.h>
#include <timer.h>
#include <bits.h>
#include <stdbool.h>

uint8_t get_timer2_mode()
{
    return 0;
}

timer_clock_divider get_timer2_clock_divider()
{
    return get_bit(AUXR, 2) == 0 ? T12 : T1;
}

bool is_timer2_P30_output_enabled()
{
    return get_bit(INT_CLKO, 2) > 0;
}
#include <sys.h>
#include <timer.h>
#include <bits.h>

uint8_t get_timer0_mode()
{
    return TMOD & 0x03;
}

timer_clock_divider_t get_timer0_clock_divider()
{
    return get_bit(AUXR, 7) == 0 ? T12 : T1;
}

bool is_timer0_P35_output_enabled()
{
    return INT_CLKO & 0x01 > 0;
}

void timer0_enable_on_pinINT0_high()
{
    bit_set(TMOD, 3);
}

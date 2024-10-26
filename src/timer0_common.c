#include <sys.h>
#include <timer.h>
#include <bits.h>

uint8_t get_timer0_mode()
{
    return TMOD & 0x03;
}

timer_clock_divider get_timer0_clock_divider()
{
    return get_bit(AUXR, 7) == 0 ? T12 : T1;
}
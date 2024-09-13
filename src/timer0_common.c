#include <sys.h>
#include <timer.h>

uint8_t get_timer0_mode()
{
    return TMOD & 0x03;
}

timer0_clock_divider get_timer0_clock_divider()
{
    return T12;
}
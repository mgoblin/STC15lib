#include <timer.h>

void timer0_mode0_enableP35_output(bool enable)
{
    enable ? bit_set(INT_CLKO, 0) : bit_clr(INT_CLKO, 0);
}

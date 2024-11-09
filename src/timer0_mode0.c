#include <timer.h>

void timer0_mode0_stop()
{
    disable_timer0_interrupt();
    TF0 = 0; // clear timer overload flag
    TR0 = 0; // clear run timer flag
}

void timer0_mode0_enableP35_output(bool enable)
{
    enable ? bit_set(INT_CLKO, 0) : bit_clr(INT_CLKO, 0);
}

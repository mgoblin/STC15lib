#include <timer.h>

void timer2_mode0_stop()
{
    bit_clr(AUXR, 4); // clear T2 run flag
    disable_timer2_interrupt();
}
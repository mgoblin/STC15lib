#include <sys.h>
#include <timer.h>
#include <bits.h>

bool is_timer0_P35_output_enabled()
{
    return INT_CLKO & 0x01 > 0;
}

void timer0_enable_on_pinINT0_high()
{
    bit_set(TMOD, 3);
}

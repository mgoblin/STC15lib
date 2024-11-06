#include <sys.h>
#include <timer.h>
#include <bits.h>

void timer0_enable_on_pinINT0_high()
{
    bit_set(TMOD, 3);
}

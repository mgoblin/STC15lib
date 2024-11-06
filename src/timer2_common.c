#include <sys.h>
#include <timer.h>
#include <bits.h>
#include <stdbool.h>

bool is_timer2_P30_output_enabled()
{
    return get_bit(INT_CLKO, 2) > 0;
}
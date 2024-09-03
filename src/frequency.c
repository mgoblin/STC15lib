#include <sys.h>
#include <frequency.h>

inline const unsigned long get_master_clock_frequency()
{
    return MAIN_Fosc;
}

const int get_master_clock_frequency_high_part() {
    return MAIN_FoscH;
}

const int get_master_clock_frequency_low_part()
{
    return MAIN_FoscL;
}
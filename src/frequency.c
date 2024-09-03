#include <sys.h>
#include <frequency.h>

inline const unsigned long get_master_clock_frequency()
{
    return MAIN_Fosc;
}

inline const int get_master_clock_frequency_high_part() {
    return MAIN_FoscH;
}

inline const int get_master_clock_frequency_low_part()
{
    return MAIN_FoscL;
}
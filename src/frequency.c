#include <sys.h>
#include <bits.h>
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

inline uint8_t get_frequency_divider()
{
    return 1 << and_mask(CLK_DIV, 0b00000111);
}
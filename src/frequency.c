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

inline uint8_t update_and_get_frequency_divider(uint8_t divider_scale)
{
    if (divider_scale < 8)
    {
        CLK_DIV |= divider_scale;
    }
    return get_frequency_divider();
}

inline void enable_master_clock_output_div1()
{
    bit_set(CLK_DIV, 6);
}

inline void enable_master_clock_output_div2()
{
    bit_set(CLK_DIV, 7);
}

inline void enable_master_clock_output_div4()
{
    bit_set(CLK_DIV, 7);
    bit_set(CLK_DIV, 6);
}
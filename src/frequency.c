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

inline uint8_t get_frequency_divider()
{
    return 1 << (CLK_DIV & 0x07);
}

inline uint8_t update_and_get_frequency_divider(uint8_t divider_scale)
{
    if (divider_scale < 8)
    {
        CLK_DIV &= (0xf8 | divider_scale);
    }
    return get_frequency_divider();
}

inline void enable_master_clock_output_div1()
{
    CLK_DIV |= 0x40; //set bit 6 of CLK_DIV
}

inline void enable_master_clock_output_div2()
{
    CLK_DIV |= 0x80; //set bit 7 of CLK_DIV
}

inline void enable_master_clock_output_div4()
{
    CLK_DIV |= 0xC0; // set bits 6 and 7 
}

inline void disable_master_clock_output()
{
    CLK_DIV &= 0x3f; // clear bits 6 and 7 
}

inline master_clock_output_pin get_master_clock_output_pin()
{
    if ((CLK_DIV & 0xC0) == 0)
    {
        return NONE;
    }
    
    return (CLK_DIV & 0x08) == 0 ? P5_4 : P1_6;
}

inline void set_master_clock_output_pin(master_clock_output_pin pin)
{
    if (pin == NONE)
    {
        disable_master_clock_output();
    } 
    else if (pin == P5_4) 
    {
        CLK_DIV &= 0xf7; // clear bit 3 of CLK_DIV
    }
    else if (pin == P1_6) 
    {
        CLK_DIV |= 0x08; // set bit 3 of CLK_DIV
    }
}
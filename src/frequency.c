#include <frequency.h>

master_clock_output_pin_t get_master_clock_output_pin()
{
    if ((CLK_DIV & 0xC0) == 0)
    {
        return NONE;
    }
    
    return (CLK_DIV & 0x08) == 0 ? P5_4 : P1_6;
}

void set_master_clock_output_pin(master_clock_output_pin_t pin)
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
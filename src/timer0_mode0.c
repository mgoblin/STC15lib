#include <timer.h>

void timer0_start(uint16_t value)
{
    // Load timer high and low bytes value
    TL0 = value & 0xff;
    TH0 = (value >> 8) & 0xff;

    enable_timer0_interrupt();

    TF0 = 0; // clear timer overload flag
    TR0 = 1; // set run timer flag

    // Atfer method call finished interrupt handler will be called on timer overload 
    // and timer will restore high and low bytes value automatically
}

void timer0_mode0_stop()
{
    disable_timer0_interrupt();
    TF0 = 0; // clear timer overload flag
    TR0 = 0; // clear run timer flag
}

void timer0_mode0_enableP35_output(bool enable)
{
    enable ? bit_set(INT_CLKO, 0) : bit_clr(INT_CLKO, 0);
}

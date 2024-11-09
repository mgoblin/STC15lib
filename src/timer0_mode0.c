#include <timer.h>

void timer0_mode0_run_once_and_wait(uint16_t value)
{
    // Load timer high and low bytes value
    TL0 = (uint8_t) value;
    TH0 = (uint8_t) bit_shift_left(value, 7);

    TF0 = 0; // clear timer overload flag
    TR0 = 1; // set run timer flag

    // Waiting for timer overloaded (timer overload flag set to 1)
    while(!TF0)
    {
    }

    TR0 = 0; // clear run timer flag
    TF0 = 0; // clear timer overload flag
}

void timer0_mode0_start(uint8_t th_value, uint8_t tl_value)
{
    // Load timer high and low bytes value
    TL0 = tl_value;
    TH0 = th_value;

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

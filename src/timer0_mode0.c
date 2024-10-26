#include <sys.h>
#include <timer.h>
#include <bits.h>

void timer0_mode0_12T_init()
{ 
    EA = 1; // set global interrupts enabled flag
    TMOD &= 0xf0; // clear all T0 flags
    bit_clr(AUXR, 7); // 12T input clock mode
}

void timer0_mode0_1T_init()
{
    EA = 1; // set global interrupts enabled flag
    //TODO dont set T1 bits
    TMOD &= 0xf0; // clear all T0 flags
    bit_set(AUXR, 7); // 1T input clock mode
}

void timer0_mode0_run_once_and_wait(uint8_t tl_value, uint8_t th_value)
{
    // Load timer high and low bytes value
    TL0 = tl_value;
    TH0 = th_value;

    TF0 = 0; // clear timer overload flag
    TR0 = 1; // set run timer flag

    // Waiting for timer overloaded (timer overload flag set to 1)
    while(!TF0)
    {
    }

    TR0 = 0; // clear timer overload flag
    TF1 = 0; // clear run timer flag
}

void timer0_mode0_start(uint8_t th_value, uint8_t tl_value)
{
    // Load timer high and low bytes value
    TL0 = tl_value;
    TH0 = th_value;

    ET0 = 1; // set timer0 interrupt enabled flag. Global interrupt enabled flag set on init.

    TF0 = 0; // clear timer overload flag
    TR0 = 1; // set run timer flag

    // Atfer method call finished interrupt handler will be called on timer overload 
    // and timer will restore high and low bytes value automatically
}

void timer0_mode0_stop()
{
    ET0 = 0; // disable timer interrupt
    TF0 = 0; // clear timer overload flag
    TR0 = 0; // clear run timer flag
}

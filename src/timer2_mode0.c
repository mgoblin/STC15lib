#include <timer.h>

void timer2_mode0_start(uint8_t th_value, uint8_t tl_value)
{
    // Load high and low timer value bytes
    T2L = tl_value;
    T2H = th_value;

    //bit_set(AUXR, 4); // set T2 run flag
    AUXR |= 0x10; //0b00010000;
}

void timer2_mode0_stop()
{
    //bit_clr(AUXR, 4); // clear T2 run flag
    AUXR &= 0xef; //0b11101111;
    disable_timer2_interrupt();
}
#include <timer.h>

void timer2_mode0_start(uint16_t tick)
{
    uint16_t value = 0xffff - tick;
    /* Load high and low timer value bytes */
    T2L = value & 0xff;
    T2H = (value >> 8) & 0xff;

    /* bit_set(AUXR, 4); // set T2 run flag */
    AUXR |= 0x10; /* 0b00010000 ; */
}

void timer2_mode0_stop()
{
    //bit_clr(AUXR, 4); // clear T2 run flag
    AUXR &= 0xef; //0b11101111;
    disable_timer2_interrupt();
}
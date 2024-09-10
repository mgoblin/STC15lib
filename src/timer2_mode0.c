#include <sys.h>
#include <time.h>

void timer2_mode0_12T_init()
{
    EA = 1; // all interrupts enabled
    //bit_clr(AUXR, 4); // clear T2 run flag
    //bit_clr(AUXR, 3); // clear T/C flag for set timer mode
    //bit_clr(AUXR, 2); // clear T2 T2x12 flag for set 12T mode
    AUXR &= 0xE3;//0b11100011;

    IE2 |= 0x04; // enable timer2 interrupt
}
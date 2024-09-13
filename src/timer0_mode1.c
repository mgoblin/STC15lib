#include <sys.h>
#include <time.h>
#include <bits.h>

void timer0_mode1_12T_init()
{
    EA = 1; // set global interrupts enabled flag
    TMOD &= 0xf0; // clear all T0 flags
    TMOD |= 0x01; // set bit 0;
    bit_clr(AUXR, 7); // 12T input clock mode
}
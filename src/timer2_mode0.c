#include <sys.h>
#include <time.h>
#include <stdint.h>
#include <stdbool.h>
#include <bits.h>
#include <interrupts.h>

void timer2_mode0_12T_init()
{
    enable_mcu_interrupts();
    //bit_clr(AUXR, 4); // clear T2 run flag
    //bit_clr(AUXR, 3); // clear T/C flag for set timer mode
    //bit_clr(AUXR, 2); // clear T2 T2x12 flag for set 12T mode
    AUXR &= 0xE3;//0b11100011;

    IE2 |= 0x04; // enable timer2 interrupt
}

void timer2_mode0_1T_init()
{
    enable_mcu_interrupts();
    //bit_clr(AUXR, 4); // clear T2 run flag
    //bit_clr(AUXR, 3); // clear T/C flag for set timer mode
    //bit_set(AUXR, 2); // set T2 T2x12 flag for set 1T mode
    AUXR &= 0xE7;//0b11100111;

    IE2 |= 0x04; // enable timer2 interrupt
}

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
}

void timer2_mode0_enableP30_output(bool enable)
{
    enable ? bit_set(INT_CLKO, 2) : bit_clr(INT_CLKO, 2);
}
#include <timer.h>
#include <timer0.h>

void timer0_mode1_12T_init()
{
    enable_mcu_interrupts();
    TMOD &= 0xf0; // clear all T0 flags
    TMOD |= 0x01; // set bit 0;
    bit_clr(AUXR, 7); // 12T input clock mode
}

void timer0_mode1_run_once_and_wait(uint8_t th_value, uint8_t tl_value)
{
    timer0_mode0_run_once_and_wait(th_value, tl_value);
}
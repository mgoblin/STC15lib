#include <timer.h>
#include <timer0.h>

void timer0_mode1_1T_init()
{
    enable_mcu_interrupts();
    TMOD &= 0xf0;
    TMOD |= 0x01;
    bit_set(AUXR, 7);
}

void timer0_mode1_run_once_and_wait(uint8_t th_value, uint8_t tl_value)
{
    timer0_mode0_run_once_and_wait(th_value, tl_value);
}
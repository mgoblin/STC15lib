#include <counter0_mode0.h>

void counter0_mode0_init()
{
    enable_mcu_interrupts();
    enable_timer0_interrupt();

    // TMOD.3/GATE = 0;
    // TMOD.2/(Timer or Counter mode) = 1;
    // TMOD.1/M1 timer0 = 0; 
    // TMOD.0/M0 timer0= 0;
    TMOD |= 0x04; // init Counter0
}

void counter0_mode0_start(uint16_t value)
{
    counter0_mode0_set_value(value);
    TF0 = 0;
    TR0 = 1;
}

void counter0_mode0_set_value(uint16_t value)
{
    TH0 = (uint8_t)(value >> 8);
    TL0 = (uint8_t)(value & 0xff);
}

uint16_t counter0_mode0_get_value()
{
    return (((uint16_t) TH0) << 8) | TL0;
}

void counter0_mode0_stop()
{
    TR0 = 0;
}

bool is_counter0_mode0_started()
{
    return TR0 == 1;
}
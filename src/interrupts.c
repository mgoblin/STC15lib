#include<interrupts.h>

void enable_mcu_interrupts()
{
    EA = 1;
}

void disable_mcu_interrupts()
{
    EA = 0;
}

bool is_mcu_interrupts_enabled()
{
    return EA == 1;
}

void enable_low_voltage_interrupt()
{
    ELVD = 1;
}

void disable_low_voltage_interrupt()
{
    ELVD = 0;
}

bool is_low_voltage_interrupt_enabled()
{
    return ELVD = 1;
}
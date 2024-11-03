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
    return ELVD == 1 && is_mcu_interrupts_enabled();
}

void enable_adc_interrupt()
{
    EADC = 1;
}

void disable_adc_interrupt()
{
    EADC = 0;
}

bool is_adc_interrupt_enabled()
{
    return EADC == 1 && is_mcu_interrupts_enabled();
}

void enable_uart1_interrupt()
{
    ES = 1;
}

void disable_uart1_interrupt()
{
    ES = 0;
}

bool is_uart1_interrupt_enabled()
{
    return ES == 1 && is_mcu_interrupts_enabled();
}

void enable_int0_interrupt()
{
    EX0 = 1;
}

void disable_int0_interrupt()
{
    EX0 = 0;
}

bool is_int0_interrupt_enabled()
{
    return EX0 == 1 && is_mcu_interrupts_enabled();
}
#include<interrupts.h>
#include<bits.h>

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

void enable_int1_interrupt()
{
    EX1 = 1;
}

void disable_int1_interrupt()
{
    EX1 = 0;
}

bool is_int1_interrupt_enabled()
{
    return EX1 == 1 && is_mcu_interrupts_enabled(); 
}

void enable_timer0_interrupt()
{
    ET0 = 1;
}

void disable_timer0_interrupt()
{
    ET0 = 0;
}

bool is_timer0_interrupt_enabled()
{
    return ET0 == 0 && is_mcu_interrupts_enabled();
}

void enable_timer2_interrupt()
{
    //ET2 = 1;
    bit_set(IE2, 2);   
}

void disable_timer2_interrupt()
{
    //ET2 = 0;
    bit_clr(IE2, 2);
}

bool is_timer2_interrupt_enabled()
{
    return test_if_bit_set(IE2, 2) && is_mcu_interrupts_enabled();
}

void enable_spi_interrupt()
{
    //ESPI = 1;
    bit_set(IE2, 1);
}

void disable_spi_interrupt()
{
    //ESPI = 0;
    bit_clr(IE2, 1);
}

bool is_spi_interrupt_enabled()
{
    return test_if_bit_set(IE2, 1) && is_mcu_interrupts_enabled();
}

void enable_int2_interrupt()
{
    //EX2 = 1;
    bit_set(INT_CLKO, 4);
}

void disable_int2_interrupt()
{
    //EX2 = 0;
    bit_clr(INT_CLKO, 4);
}

bool is_int2_interrupt_enabled()
{
    return test_if_bit_set(INT_CLKO, 4) && is_mcu_interrupts_enabled();
}
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

void enable_int3_interrupt()
{
    //EX3 = 1;
    bit_set(INT_CLKO, 5);
}

void disable_int3_interrupt()
{
    //EX3 = 0;
    bit_clr(INT_CLKO, 5);
}

bool is_int3_interrupt_enabled()
{
    return test_if_bit_set(INT_CLKO, 5) && is_mcu_interrupts_enabled();
}

void enable_int4_interrupt()
{
    //EX4 = 1;
    bit_set(INT_CLKO, 6);
}

void disable_int4_interrupt()
{
    //EX4 = 0;
    bit_clr(INT_CLKO, 6);
}

bool is_int4_interrupt_enable()
{
    return test_if_bit_set(INT_CLKO, 6) && is_mcu_interrupts_enabled();
}

void set_pca_interrupt_priority(interrupt_priority_t priority)
{
    PPCA = priority;
}

interrupt_priority_t get_pca_interrupt_priority()
{
    return PPCA;
}

void set_low_voltage_interrupt_priority(interrupt_priority_t priority)
{
    PLVD = priority;
}

interrupt_priority_t get_low_voltage_interrupt_priority()
{
    return PLVD;
}

void set_adc_interrupt_priority(interrupt_priority_t priority)
{
    PADC = priority;
}

interrupt_priority_t get_adc_interrupt_priority()
{
    return PADC;
}

void set_uart1_interrupt_priority(interrupt_priority_t priority)
{
    PS = priority;
}

interrupt_priority_t get_uart1_interrupt_priority()
{
    return PS;
}

void set_int0_interrupt_priority(interrupt_priority_t priority)
{
    PX0 = priority;
}

interrupt_priority_t get_int0_interrupt_priority()
{
    return PX0;
}

void set_int1_interrupt_priority(interrupt_priority_t priority)
{
    PX1 = priority;
}

interrupt_priority_t get_int1_interrupt_priority()
{
    return PX1;
}

void set_timer0_interrupt_priority(interrupt_priority_t priority)
{
    PT0 = priority;
}

interrupt_priority_t get_timer0_interrupt_priority()
{
    return PT0;
}

void set_spi_interrupt_priority(interrupt_priority_t priority)
{
    priority == HIGH ? bit_set(IP2, 1) : bit_clr(IP2, 1); 
}

interrupt_priority_t get_spi_interrupt_priority()
{
    return test_if_bit_set(IE2, 1);
}

void set_int0_interrupt_trigger(external_interrupt_trigger_t trigger)
{
    IT0 = trigger;
}

external_interrupt_trigger_t get_int0_interrupt_trigger()
{
    return IT0;
}

void set_int1_interrupt_trigger(external_interrupt_trigger_t trigger)
{
    IT1 = trigger;
}

external_interrupt_trigger_t get_int1_interrupt_trigger()
{
    return IT1;
}
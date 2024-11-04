#include<interrupts.h>
#include<bits.h>

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
#include<interrupts.h>
#include<bits.h>

void set_int1_interrupt_trigger(external_interrupt_trigger_t trigger)
{
    IT1 = trigger;
}

external_interrupt_trigger_t get_int1_interrupt_trigger()
{
    return IT1;
}
#include<sys.h>
#include<interrupts.h>

void enabled_all_interrupts()
{
    EA = 1;
}

void disable_all_interrupts()
{
    EA = 0;
}

bool is_interrupts_enabled()
{
    return EA == 1;
}
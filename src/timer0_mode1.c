#include <timer.h>
#include <timer0.h>

void timer0_mode1_run_once_and_wait(uint16_t value)
{
    timer0_mode0_run_once_and_wait(value);
}
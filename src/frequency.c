#include <sys/sys.h>
#include <frequency/frequency.h>

const unsigned long get_cpu_frequency()
{
    return MAIN_Fosc;
}

const int get_cpu_frequency_high_part() {
    return MAIN_FoscH;
}

const int get_cpu_frequency_low_part()
{
    return MAIN_FoscL;
}
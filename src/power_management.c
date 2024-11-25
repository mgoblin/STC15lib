#include <power_management.h>

void idle()
{
    bit_set(PCON, 0);
}
#include <reset.h>

void reset()
{
    bit_set(IAP_CONTR, 5);    
}
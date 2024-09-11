#include <sys.h>
#include <frequency.h>

#define LED P10

void main()
{
    //CLK_DIV = 0xC0;
    enable_master_clock_output_div1();

    while (1);
    
}
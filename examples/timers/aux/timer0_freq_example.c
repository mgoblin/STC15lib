#include <sys.h>
#include <delay.h>
#include <timer.h>

void timer0ISR(void) __interrupt(1)
{

}

void main()
{
    // When T0 in 12T mode (AUXR.7/T0x12=1), 
    // the output frequency = (SYSclk/12)/(65536-[RL_TH0, RL_TL0])/2

    // TH0 = 0xff and HL = 0xff. 65536-[RL_TH0, RL_TL0] = 1
    // Frequency = SysClk/24.
    // When frequency divider = 1, then SysClk = MainFosc
    // Frequency = MainFosc/24 = 11059200 / 24 = 460 800 Hz =  460.8 khz
    // Mesurement result is 461.538 kHz, 
    // high pin time is 1.125 micro sec, low pin time is 1.042 micro sec
    
    // 64 628 = 0xFC74

    timer0_mode0_12T_init();

    timer0_mode0_enableP35_output(true);

    timer0_mode0_start(0xfc, 0x64);
    

    while (1) {}
}
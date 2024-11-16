#include <timer_to_ms.h>

uint32_t timer_uint16_ticks_to_freq(uint16_t ticks)
{
    // When timer0 in 12T mode (AUXR.7/T0x12=1), 
    // the output frequency = (SYSclk/12)/((65536-[RL_TH0, RL_TL0]) * 2)

    // TH0 = 0xff and HL = 0xff. 65536-[RL_TH0, RL_TL0] = 1
    // Frequency = SysClk/24.
    // When frequency divider = 1, then SysClk = MainFosc
    // Frequency = MainFosc/24 = 11059200 / 24 = 460 800 Hz =  460.8 kHz
    // Mesurement result is 461.538 kHz, 
    // high pin time is 1.125 micro sec, low pin time is 1.042 micro sec

    //TH0 = 0x00 and HL = 0x00. 65536-[RL_TH0, RL_TL0] = 65536
    // Frequency = SysClk/(24 * 65536) = SysClk/1572864.
    // When frequency divider = 1, then SysClk = MainFosc
    // Frequency = MainFosc/1572864 = 11059200 / 1572864 = 7,031 Hz =  7 Hz
    // Mesurement result is 7.041 Hz
    // high pin time is 71.01 milli sec, low pin time is 7.02 milli sec

    uint32_t ticks_divider = 1 + (uint32_t)ticks;
    uint32_t freq = get_master_clock_frequency() / (12 * 2 * ticks_divider);
    //TODO 1T vs 12T
    return (100 * freq) / get_frequency_divider();
}

uint16_t timer_frequency_to_ticks(uint32_t frequency)
{
    // TODO Corner cases for fequency parameter value
    uint16_t th_regs = 65536 - (get_master_clock_frequency() / (12 * 2 * frequency));
    return 0xffff - th_regs;
}
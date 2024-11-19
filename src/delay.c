#include <delay.h>

void delay_ms_asm(uint8_t ms, uint8_t freq_scale)
{
    // b = 8, a = 236 => a * b = 1888 => 1.00225 ms
    //load freq_scale + 1 to register b;
    ms;
    freq_scale;
    __asm;
    ; first argument in in dpl
    inc dpl
    delay$:
        mov	b, #9
    outer$:
        mov	a, _delay_ms_asm_PARM_2 ; j
    inner$:
        djnz acc, inner$
        djnz b, outer$
        djnz dpl, delay$
    __endasm;
}

void delay_ms(uint16_t ms)
{
    uint8_t ms_high = ms >> 8;
    uint8_t ms_low = ms & 0xff;
    uint8_t scale = 255 >> get_frequency_divider_scale();
    do
    {
        delay_ms_asm(ms_low, scale);
    } while (ms_high--);
}

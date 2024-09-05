#ifndef STC15_TIMERH
#define STC15_TIMERH

#include <stdint.h>

typedef enum {
    TIMER0,
    TIMER1
} timer_id;

typedef enum {
    TIMER, COUNTER
} timer_type;

typedef enum {
    MODE0,
    MODE1,
    MODE2,
    MODE3
} timer_mode;

void timer_mode0_init(const timer_id timerid);
void timer_mode0_run_and_wait(const timer_id timerid, uint8_t tl_value, uint8_t th_value);

#endif
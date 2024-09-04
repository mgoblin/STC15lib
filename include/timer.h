#ifndef STC15_TIMERH
#define STC15_TIMERH

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

void init_timer(const timer_id timerid, const timer_type timertype, timer_mode timermode);

#endif
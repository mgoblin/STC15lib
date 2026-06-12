add_library(stc15hal STATIC
  uart.c
  timer_ticks_to_ms.c
  timer_ms_to_ticks.c
  timer8bit_ticks_to_mcs.c
  timer_ticks_to_Hz.c
  timer_Hz_to_ticks.c
  timer_Hz_to_ticks_8bit.c
  timer_ms_to_ticks_table.c
) # Create libray from uart.c
add_library(stc15hal STATIC 
  uart.c
  ticks_to_ms_common.c
  timer_ms_to_ticks.c
  ticks_to_mcs_common.c
  timer_ticks_to_Hz.c
  timer_Hz_to_ticks.c
  timer_Hz_to_ticks_8bit.c
) # Create libray from uart.c
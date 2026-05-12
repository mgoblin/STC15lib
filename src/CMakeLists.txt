add_library(stc15lib STATIC 
  uart.c
  ticks_to_ms_common.c
  ms_to_ticks_common.c
  ticks_to_mcs_common.c
  timer_ticks_to_Hz.c
  timer_Hz_to_ticks.c
) # Create libray from uart.c
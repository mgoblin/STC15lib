add_executable(timer2_mode0_start_ms_example
    timer2_mode0_start_ms_example.c
)
add_executable(timer2_mode0_start_Hz_example
    timer2_mode0_start_Hz_example.c
)

target_link_libraries(timer2_mode0_start_ms_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_start_Hz_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_start_ms_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_start_Hz_example)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_start_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/ms_freq/timer2_mode0_start_ms_example.hex
    DEPENDS timer2_mode0_start_ms_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_start_Hz
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/ms_freq/timer2_mode0_start_Hz_example.hex
    DEPENDS timer2_mode0_start_Hz_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

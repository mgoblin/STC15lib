add_executable(timer0_mode3_ms_to_ticks_example
    timer0_mode3_ms_to_ticks_example.c
)

add_executable(timer0_mode3_ticks_to_ms_example
    timer0_mode3_ticks_to_ms_example.c
)

add_executable(timer0_mode3_ticks_to_Hz_example
    timer0_mode3_ticks_to_Hz_example.c
)

add_executable(timer0_mode3_Hz_to_ticks_example
    timer0_mode3_Hz_to_ticks_example.c
)

add_executable(timer0_mode3_start_ms_example
    timer0_mode3_start_ms_example.c
)

add_executable(timer0_mode3_start_Hz_example
    timer0_mode3_start_Hz_example.c
)

add_executable(timer0_mode3_delay_ms_example
    timer0_mode3_delay_ms_example.c
)

target_link_libraries(timer0_mode3_ms_to_ticks_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_ticks_to_ms_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_ticks_to_Hz_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_Hz_to_ticks_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_start_ms_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_start_Hz_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_delay_ms_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_ms_to_ticks_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_ticks_to_ms_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_ticks_to_Hz_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_Hz_to_ticks_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_start_ms_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_start_Hz_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_delay_ms_example)


# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_ms_to_ticks
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_ms_to_ticks_example.hex
    DEPENDS timer0_mode3_ms_to_ticks_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_ticks_to_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_ticks_to_ms_example.hex
    DEPENDS timer0_mode3_ticks_to_ms_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_ticks_to_Hz
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_ticks_to_Hz_example.hex
    DEPENDS timer0_mode3_ticks_to_Hz_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_Hz_to_ticks
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_Hz_to_ticks_example.hex
    DEPENDS timer0_mode3_Hz_to_ticks_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_start_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_start_ms_example.hex
    DEPENDS timer0_mode3_start_ms_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_start_Hz
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_start_Hz_example.hex
    DEPENDS timer0_mode3_start_Hz_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_delay_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/ms_freq/timer0_mode3_delay_ms_example.hex
    DEPENDS timer0_mode3_delay_ms_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

add_subdirectory("ms_freq")

add_executable(timer2_mode0_1T_interrupt_example
    timer2_mode0_1T_interrupt_example.c
)
add_executable(timer2_mode0_direct_reload_example
    timer2_mode0_direct_reload_example.c
)
add_executable(timer2_mode0_P30_output_example
    timer2_mode0_P30_output_example.c
)
add_executable(timer2_mode0_reload_example
    timer2_mode0_reload_example.c
)
add_executable(timer2_mode0_ms_to_ticks_example
    timer2_mode0_ms_to_ticks_example.c
)

add_executable(timer2_mode0_ticks_to_ms_example
    timer2_mode0_ticks_to_ms_example.c
)

add_executable(timer2_mode0_ticks_to_Hz_example
    timer2_mode0_ticks_to_Hz_example.c
)

add_executable(timer2_mode0_Hz_to_ticks_example
    timer2_mode0_Hz_to_ticks_example.c
)

target_link_libraries(timer2_mode0_1T_interrupt_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_direct_reload_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_P30_output_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_reload_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_ms_to_ticks_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_ticks_to_ms_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_ticks_to_Hz_example PRIVATE stc15hal)
target_link_libraries(timer2_mode0_Hz_to_ticks_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_1T_interrupt_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_direct_reload_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_P30_output_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_reload_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_ms_to_ticks_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_ticks_to_ms_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_ticks_to_Hz_example)
ihx_to_hex(timer2_mode0_Hz_to_ticks_example)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_1T_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_1T_interrupt_example.hex
    DEPENDS timer2_mode0_1T_interrupt_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_direct_reload
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_direct_reload_example.hex
    DEPENDS timer2_mode0_direct_reload_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_P30_output
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_P30_output_example.hex
    DEPENDS timer2_mode0_P30_output_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_reload
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_reload_example.hex
    DEPENDS timer2_mode0_reload_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_ms_to_ticks
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_ms_to_ticks_example.hex
    DEPENDS timer2_mode0_ms_to_ticks_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_ticks_to_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_ticks_to_ms_example.hex
    DEPENDS timer2_mode0_ticks_to_ms_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_ticks_to_Hz
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_ticks_to_Hz_example.hex
    DEPENDS timer2_mode0_ticks_to_Hz_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_Hz_to_ticks
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode0/timer2/timer2_mode0_Hz_to_ticks_example.hex
    DEPENDS timer2_mode0_Hz_to_ticks_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)


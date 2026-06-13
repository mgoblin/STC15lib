add_executable(timer0_mode3_1T_interrupt_example
    timer0_mode3_1T_interrupt_example.c
)
add_executable(timer0_mode3_direct_reload_example
    timer0_mode3_direct_reload_example.c
)
add_executable(timer0_mode3_direct_start_example
    timer0_mode3_direct_start_example.c
)
add_executable(timer0_mode3_pause_by_gate_example
    timer0_mode3_pause_by_gate_example.c
)
add_executable(timer0_mode3_reload_example
    timer0_mode3_reload_example.c
)

target_link_libraries(timer0_mode3_1T_interrupt_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_direct_reload_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_direct_start_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_pause_by_gate_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_reload_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_1T_interrupt_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_direct_reload_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_direct_start_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_pause_by_gate_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_reload_example)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_1T_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/async/timer0_mode3_1T_interrupt_example.hex
    DEPENDS timer0_mode3_1T_interrupt_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_direct_reload
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/async/timer0_mode3_direct_reload_example.hex
    DEPENDS timer0_mode3_direct_reload_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_direct_start
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/async/timer0_mode3_direct_start_example.hex
    DEPENDS timer0_mode3_direct_start_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_pause_by_gate
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/async/timer0_mode3_pause_by_gate_example.hex
    DEPENDS timer0_mode3_pause_by_gate_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_reload
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/async/timer0_mode3_reload_example.hex
    DEPENDS timer0_mode3_reload_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
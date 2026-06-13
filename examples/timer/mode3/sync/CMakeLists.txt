add_executable(timer0_mode3_1T_sync_example
    timer0_mode3_1T_sync_example.c
)
add_executable(timer0_mode3_12T_sync_example
    timer0_mode3_12T_sync_example.c
)

target_link_libraries(timer0_mode3_1T_sync_example PRIVATE stc15hal)
target_link_libraries(timer0_mode3_12T_sync_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_1T_sync_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode3_12T_sync_example)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_1T_sync
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/sync/timer0_mode3_1T_sync_example.hex
    DEPENDS timer0_mode3_1T_sync_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_mode3_12T_sync
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/mode3/sync/timer0_mode3_12T_sync_example.hex
    DEPENDS timer0_mode3_12T_sync_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

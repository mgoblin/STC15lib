add_executable(timer0_mode1_1T_sync_example
    timer0_mode1_1T_sync_example.c
)
add_executable(timer0_mode1_12T_sync_example
    timer0_mode1_12T_sync_example.c
)

target_link_libraries(timer0_mode1_1T_sync_example PRIVATE stc15lib)
target_link_libraries(timer0_mode1_12T_sync_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(timer0_mode1_1T_sync_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_mode1_12T_sync_example)

# upload firmware to STC MCU
add_custom_target(flash_timer0_mode1_1T_sync
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_mode1_1T_sync_example.hex
    DEPENDS timer0_mode1_1T_sync_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_mode1_12T_sync
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_mode1_12T_sync_example.hex
    DEPENDS timer0_mode1_12T_sync_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

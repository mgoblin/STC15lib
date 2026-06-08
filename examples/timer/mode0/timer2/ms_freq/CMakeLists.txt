add_executable(timer2_mode0_start_ms_example
    timer2_mode0_start_ms_example.c
)


target_link_libraries(timer2_mode0_start_ms_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_start_ms_example)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_start_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer2_mode0_start_ms_example.hex
    DEPENDS timer2_mode0_start_ms_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

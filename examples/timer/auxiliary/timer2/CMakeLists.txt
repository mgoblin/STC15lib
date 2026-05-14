add_executable(timer2_12T_freq_uint16_example
    timer2_12T_freq_uint16_example.c
)

target_link_libraries(timer2_12T_freq_uint16_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(timer2_12T_freq_uint16_example)

# upload firmware to STC MCU
add_custom_target(flash_timer2_12T_freq_uint16
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer2_12T_freq_uint16_example.hex
    DEPENDS timer2_12T_freq_uint16_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

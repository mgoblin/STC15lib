add_executable(timer0_1T_freq_uint16_example
    timer0_1T_freq_uint16_example.c
)
add_executable(timer0_12T_freq_uint8_example
    timer0_12T_freq_uint8_example.c
)
add_executable(timer0_12T_freq_uint16_example
    timer0_12T_freq_uint16_example.c
)
add_executable(timer0_12T_ticks_example
    timer0_12T_ticks_example.c
)
add_executable(timer0_ticks_to_ms_example
    timer0_ticks_to_ms_example.c
)

target_link_libraries(timer0_1T_freq_uint16_example PRIVATE stc15lib)
target_link_libraries(timer0_12T_freq_uint8_example PRIVATE stc15lib)
target_link_libraries(timer0_12T_freq_uint16_example PRIVATE stc15lib)
target_link_libraries(timer0_12T_ticks_example PRIVATE stc15lib)
target_link_libraries(timer0_ticks_to_ms_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(timer0_1T_freq_uint16_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_12T_freq_uint8_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_12T_freq_uint16_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_12T_ticks_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_ticks_to_ms_example)


# upload firmware to STC MCU
add_custom_target(flash_timer0_1T_freq_uint16
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_1T_freq_uint16_example.hex
    DEPENDS timer0_1T_freq_uint16_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_12T_freq_uint8
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_12T_freq_uint8_example.hex
    DEPENDS timer0_12T_freq_uint8_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_12T_freq_uint16
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_12T_freq_uint16_example.hex
    DEPENDS timer0_12T_freq_uint16_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_12T_ticks
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_12T_ticks_example.hex
    DEPENDS timer0_12T_ticks_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_ticks_to_ms
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_ticks_to_ms_example.hex
    DEPENDS timer0_ticks_to_ms_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

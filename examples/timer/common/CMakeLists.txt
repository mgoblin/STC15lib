add_executable(timer0_common_example
    timer0_common_example.c
)
add_executable(timer0_ms2ticks_example
    timer0_ms2ticks_example.c
)
add_executable(timer2_common_example
    timer2_common_example.c
)

target_link_libraries(timer0_common_example PRIVATE stc15lib)
target_link_libraries(timer0_ms2ticks_example PRIVATE stc15lib)
target_link_libraries(timer2_common_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(timer0_common_example)
# Transform firmware ihx to hex
ihx_to_hex(timer0_ms2ticks_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_common_example)

# upload firmware to STC MCU
add_custom_target(flash_timer0_common
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_common_example.hex
    DEPENDS timer0_common_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer0_ms2ticks
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer0_ms2ticks_example.hex
    DEPENDS timer0_ms2ticks_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer2_common_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer2_common_example.hex
    DEPENDS timer2_common_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

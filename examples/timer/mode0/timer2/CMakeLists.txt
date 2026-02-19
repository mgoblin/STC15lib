add_executable(timer2_mode0_1T_interrupt_example
    timer2_mode0_1T_interrupt_example.c
)
add_executable(timer2_mode0_direct_reload_example
    timer2_mode0_direct_reload_example.c
)
add_executable(timer2_mode0_P30_output_example
    timer2_mode0_P30_output_example.c
)

target_link_libraries(timer2_mode0_1T_interrupt_example PRIVATE stc15lib)
target_link_libraries(timer2_mode0_direct_reload_example PRIVATE stc15lib)
target_link_libraries(timer2_mode0_P30_output_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_1T_interrupt_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_direct_reload_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_mode0_P30_output_example)

# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_1T_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer2_mode0_1T_interrupt_example.hex
    DEPENDS timer2_mode0_1T_interrupt_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_direct_reload
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer2_mode0_direct_reload_example.hex
    DEPENDS timer2_mode0_direct_reload_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_timer2_mode0_P30_output_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/timer2_mode0_P30_output_example.hex
    DEPENDS timer2_mode0_P30_output_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)


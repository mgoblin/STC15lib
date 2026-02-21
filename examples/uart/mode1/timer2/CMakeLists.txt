add_executable(uart1_mode1_timer2_1T_example
    uart1_mode1_timer2_1T_example.c
)
add_executable(uart1_mode1_timer2_1T_freq_bias_example
    uart1_mode1_timer2_1T_freq_bias_example.c
)
add_executable(uart1_mode1_timer2_12T_example
    uart1_mode1_timer2_12T_example.c
)
add_executable(uart1_mode1_timer2_12T_freq_bias_example
    uart1_mode1_timer2_12T_freq_bias_example.c
)
add_executable(uart1_mode1_timer2_12T_interrupt_example
    uart1_mode1_timer2_12T_interrupt_example.c
)

target_link_libraries(uart1_mode1_timer2_1T_example PRIVATE stc15lib)
target_link_libraries(uart1_mode1_timer2_1T_freq_bias_example PRIVATE stc15lib)
target_link_libraries(uart1_mode1_timer2_12T_example PRIVATE stc15lib)
target_link_libraries(uart1_mode1_timer2_12T_freq_bias_example PRIVATE stc15lib)
target_link_libraries(uart1_mode1_timer2_12T_interrupt_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode1_timer2_1T_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode1_timer2_1T_freq_bias_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode1_timer2_12T_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode1_timer2_12T_freq_bias_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode1_timer2_12T_interrupt_example)


# upload firmware to STC MCU
add_custom_target(flash_uart1_mode1_timer2_1T
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode1_timer2_1T_example.hex
    DEPENDS uart1_mode1_timer2_1T_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_mode1_timer2_1T_freq_bias
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode1_timer2_1T_freq_bias_example.hex
    DEPENDS uart1_mode1_timer2_1T_freq_bias_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_mode1_timer2_12T
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode1_timer2_12T_example.hex
    DEPENDS uart1_mode1_timer2_12T_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_mode1_timer2_12T_freq_bias
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode1_timer2_12T_freq_bias_example.hex
    DEPENDS uart1_mode1_timer2_12T_freq_bias_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_mode1_timer2_12T_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode1_timer2_12T_interrupt_example.hex
    DEPENDS uart1_mode1_timer2_12T_interrupt_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

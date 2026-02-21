add_executable(uart1_mode0_baud_rates_example
    uart1_mode0_baud_rates_example.c
)
add_executable(uart1_mode0_send_example
    uart1_mode0_send_example.c
)

target_link_libraries(uart1_mode0_baud_rates_example PRIVATE stc15lib)
target_link_libraries(uart1_mode0_send_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode0_baud_rates_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode0_send_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode0_baud_rates
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode0_baud_rates_example.hex
    DEPENDS uart1_mode0_baud_rates_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_mode0_send
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode0_send_example.hex
    DEPENDS uart1_mode0_send_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

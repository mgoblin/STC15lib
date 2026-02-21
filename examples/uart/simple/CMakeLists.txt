add_executable(uart_example
    uart_example.c
)

target_link_libraries(uart_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(uart_example)

# upload firmware to STC MCU
add_custom_target(flash_uart
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart_example.hex
    DEPENDS uart_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

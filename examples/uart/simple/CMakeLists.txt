add_executable(uart_example
    uart_example.c
)

target_link_libraries(uart_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(uart_example)

# upload firmware to STC MCU
add_custom_target(flash_uart
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/simple/uart_example.hex
    DEPENDS uart_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

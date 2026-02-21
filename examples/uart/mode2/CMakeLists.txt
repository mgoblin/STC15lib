add_executable(uart1_mode2_receive_odd_parity_example
    uart1_mode2_receive_odd_parity_example.c
)
add_executable(uart1_mode2_send_9bit_example
    uart1_mode2_send_9bit_example.c
)
add_executable(uart1_mode2_send_odd_parity_example
    uart1_mode2_send_odd_parity_example.c
)

target_link_libraries(uart1_mode2_receive_odd_parity_example PRIVATE stc15lib)
target_link_libraries(uart1_mode2_send_9bit_example PRIVATE stc15lib)
target_link_libraries(uart1_mode2_send_odd_parity_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode2_receive_odd_parity_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode2_send_9bit_example)
# Transform firmware ihx to hex
ihx_to_hex(uart1_mode2_send_odd_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode2_receive_odd_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode2_receive_odd_parity_example.hex
    DEPENDS uart1_mode2_receive_odd_parity_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_uart1_mode2_send_9bit
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode2_send_9bit_example.hex
    DEPENDS uart1_mode2_send_9bit_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_uart1_mode2_send_odd_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode2_send_odd_parity_example.hex
    DEPENDS uart1_mode2_send_odd_parity_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

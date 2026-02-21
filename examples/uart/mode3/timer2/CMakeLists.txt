# 1
add_executable(uart1_mode3_timer2_1T_2stop_bits_example
    uart1_mode3_timer2_1T_2stop_bits_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_2stop_bits_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_2stop_bits_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T_2stop_bits
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_1T_2stop_bits_example.hex
    DEPENDS uart1_mode3_timer2_1T_2stop_bits_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 2
add_executable(uart1_mode3_timer2_1T_example
    uart1_mode3_timer2_1T_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_1T_example.hex
    DEPENDS uart1_mode3_timer2_1T_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 3
add_executable(uart1_mode3_timer2_1T_freq_bias_example
    uart1_mode3_timer2_1T_freq_bias_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_freq_bias_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_freq_bias_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T_freq_bias
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_1T_freq_bias_example.hex
    DEPENDS uart1_mode3_timer2_1T_freq_bias_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 4
add_executable(uart1_mode3_timer2_1T_odd_parity_example
    uart1_mode3_timer2_1T_odd_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_odd_parity_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_odd_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T_odd_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_1T_odd_parity_example.hex
    DEPENDS uart1_mode3_timer2_1T_odd_parity_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 5
add_executable(uart1_mode3_timer2_12T_even_parity_example
    uart1_mode3_timer2_12T_even_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_even_parity_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_even_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_even_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_12T_even_parity_example.hex
    DEPENDS uart1_mode3_timer2_12T_even_parity_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 6
add_executable(uart1_mode3_timer2_12T_example
    uart1_mode3_timer2_12T_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_12T_example.hex
    DEPENDS uart1_mode3_timer2_12T_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 7
add_executable(uart1_mode3_timer2_12T_freq_bias_example
    uart1_mode3_timer2_12T_freq_bias_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_freq_bias_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_freq_bias_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_freq_bias_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_12T_freq_bias_example.hex
    DEPENDS uart1_mode3_timer2_12T_examuart1_mode3_timer2_12T_freq_bias_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 8
add_executable(uart1_mode3_timer2_12T_interrupt_example
    uart1_mode3_timer2_12T_interrupt_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_interrupt_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_interrupt_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_12T_interrupt_example.hex
    DEPENDS uart1_mode3_timer2_12T_interrupt_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 9
add_executable(uart1_mode3_timer2_12T_receive_even_parity_example
    uart1_mode3_timer2_12T_receive_even_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_receive_even_parity_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_receive_even_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_receive_even_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_12T_receive_even_parity_example.hex
    DEPENDS uart1_mode3_timer2_12T_receive_even_parity_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# 10
add_executable(uart1_mode3_timer2_12T_receive_odd_parity_example
    uart1_mode3_timer2_12T_receive_odd_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_receive_odd_parity_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_receive_odd_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_receive_odd_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/uart1_mode3_timer2_12T_receive_odd_parity_example.hex
    DEPENDS uart1_mode3_timer2_12T_receive_odd_parity_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

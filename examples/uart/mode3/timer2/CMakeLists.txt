# 1
add_executable(uart1_mode3_timer2_1T_2stop_bits_example
    uart1_mode3_timer2_1T_2stop_bits_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_2stop_bits_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_2stop_bits_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T_2stop_bits
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_1T_2stop_bits_example.hex
    DEPENDS uart1_mode3_timer2_1T_2stop_bits_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 2
add_executable(uart1_mode3_timer2_1T_example
    uart1_mode3_timer2_1T_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_1T_example.hex
    DEPENDS uart1_mode3_timer2_1T_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 3
add_executable(uart1_mode3_timer2_1T_freq_bias_example
    uart1_mode3_timer2_1T_freq_bias_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_freq_bias_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_freq_bias_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T_freq_bias
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_1T_freq_bias_example.hex
    DEPENDS uart1_mode3_timer2_1T_freq_bias_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 4
add_executable(uart1_mode3_timer2_1T_odd_parity_example
    uart1_mode3_timer2_1T_odd_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_1T_odd_parity_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_1T_odd_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_1T_odd_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_1T_odd_parity_example.hex
    DEPENDS uart1_mode3_timer2_1T_odd_parity_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 5
add_executable(uart1_mode3_timer2_12T_even_parity_example
    uart1_mode3_timer2_12T_even_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_even_parity_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_even_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_even_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_12T_even_parity_example.hex
    DEPENDS uart1_mode3_timer2_12T_even_parity_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 6
add_executable(uart1_mode3_timer2_12T_example
    uart1_mode3_timer2_12T_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_12T_example.hex
    DEPENDS uart1_mode3_timer2_12T_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 7
add_executable(uart1_mode3_timer2_12T_freq_bias_example
    uart1_mode3_timer2_12T_freq_bias_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_freq_bias_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_freq_bias_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_freq_bias_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_12T_freq_bias_example.hex
    DEPENDS uart1_mode3_timer2_12T_examuart1_mode3_timer2_12T_freq_bias_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 8
add_executable(uart1_mode3_timer2_12T_interrupt_example
    uart1_mode3_timer2_12T_interrupt_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_interrupt_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_interrupt_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_12T_interrupt_example.hex
    DEPENDS uart1_mode3_timer2_12T_interrupt_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 9
add_executable(uart1_mode3_timer2_12T_receive_even_parity_example
    uart1_mode3_timer2_12T_receive_even_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_receive_even_parity_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_receive_even_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_receive_even_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_12T_receive_even_parity_example.hex
    DEPENDS uart1_mode3_timer2_12T_receive_even_parity_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# 10
add_executable(uart1_mode3_timer2_12T_receive_odd_parity_example
    uart1_mode3_timer2_12T_receive_odd_parity_example.c
)

target_link_libraries(uart1_mode3_timer2_12T_receive_odd_parity_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(uart1_mode3_timer2_12T_receive_odd_parity_example)

# upload firmware to STC MCU
add_custom_target(flash_uart1_mode3_timer2_12T_receive_odd_parity
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/uart/mode3/timer2/uart1_mode3_timer2_12T_receive_odd_parity_example.hex
    DEPENDS uart1_mode3_timer2_12T_receive_odd_parity_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

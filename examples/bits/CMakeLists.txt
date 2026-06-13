add_executable(bits_example
    bits_example.c
)

target_link_libraries(bits_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(bits_example)

# upload firmware to STC MCU
add_custom_target(flash_bits
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/bits/bits_example.hex
    DEPENDS bits_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

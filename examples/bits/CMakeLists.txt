add_executable(bits_example
    bits_example.c
)

target_link_libraries(bits_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(bits_example)

# upload firmware to STC MCU
add_custom_target(flash_bits
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/bits_example.hex
    DEPENDS adc_async_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

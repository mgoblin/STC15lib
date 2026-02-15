add_executable(pin_read_value_example
    pin_read_value_example.c
)

target_link_libraries(pin_read_value_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(pin_read_value_example)

# upload firmware to STC MCU
add_custom_target(flash_pin_read_value
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/pin_read_value_example.hex
    DEPENDS pin_read_value_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

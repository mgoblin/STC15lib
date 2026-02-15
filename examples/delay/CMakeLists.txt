add_executable(delay_example
    delay_example.c
)

target_link_libraries(delay_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(delay_example)

# upload firmware to STC MCU
add_custom_target(flash_delay
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/delay_example.hex
    DEPENDS delay_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

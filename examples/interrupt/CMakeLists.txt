add_executable(interrupt_example
    interrupt_example.c
)

target_link_libraries(interrupt_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(interrupt_example)

# upload firmware to STC MCU
add_custom_target(flash_interrupt
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/interrupt_example.hex
    DEPENDS interrupt_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

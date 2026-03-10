add_executable(interrupt_int0_example
    interrupt_int0_example.c
)
add_executable(interrupt_int1_example
    interrupt_int1_example.c
)

target_link_libraries(interrupt_int0_example PRIVATE stc15lib) 
target_link_libraries(interrupt_int1_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(interrupt_int0_example)
# Transform firmware ihx to hex
ihx_to_hex(interrupt_int1_example)

# upload firmware to STC MCU
add_custom_target(flash_interrupt_int0
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/interrupt_int0_example.hex
    DEPENDS interrupt_int0_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# upload firmware to STC MCU
add_custom_target(flash_interrupt_int1
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/interrupt_int1_example.hex
    DEPENDS interrupt_int1_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

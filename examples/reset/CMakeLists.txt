add_executable(reset_example
    reset_example.c
)

target_link_libraries(reset_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(reset_example)

# upload firmware to STC MCU
add_custom_target(flash_reset
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/reset_example.hex
    DEPENDS reset_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

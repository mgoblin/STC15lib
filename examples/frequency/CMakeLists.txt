add_executable(master_clock_output_example
    master_clock_output_example.c
)
add_executable(slowdown_example
    slowdown_example.c
)

target_link_libraries(master_clock_output_example PRIVATE stc15lib)
target_link_libraries(slowdown_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(master_clock_output_example)
# Transform firmware ihx to hex
ihx_to_hex(slowdown_example)


# upload firmware to STC MCU
add_custom_target(flash_master_clock_output
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/master_clock_output_example.hex
    DEPENDS master_clock_output_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_slowdown
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/slowdown_example.hex
    DEPENDS slowdown_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

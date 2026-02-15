add_executable(counter0_mode1_example
    counter0_mode1_example.c
)

target_link_libraries(counter0_mode1_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(counter0_mode1_example)

# upload firmware to STC MCU
add_custom_target(flash_counter0_mode1
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/counter0_mode1_example.hex
    DEPENDS counter0_mode1_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

add_executable(counter2_mode0_example
    counter2_mode0_example.c
)

target_link_libraries(counter2_mode0_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(counter2_mode0_example)

# upload firmware to STC MCU
add_custom_target(flash_counter2_mode0
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/counter2_mode0_example.hex
    DEPENDS counter2_mode0_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

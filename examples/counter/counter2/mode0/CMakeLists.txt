add_executable(counter2_mode0_example
    counter2_mode0_example.c
)

target_link_libraries(counter2_mode0_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(counter2_mode0_example)

# upload firmware to STC MCU
add_custom_target(flash_counter2_mode0
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/counter/counter2/mode0/counter2_mode0_example.hex
    DEPENDS counter2_mode0_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

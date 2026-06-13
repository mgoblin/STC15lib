add_executable(counter0_mode1_example
    counter0_mode1_example.c
)

target_link_libraries(counter0_mode1_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(counter0_mode1_example)

# upload firmware to STC MCU
add_custom_target(flash_counter0_mode1
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/counter/counter0/mode1/counter0_mode1_example.hex
    DEPENDS counter0_mode1_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

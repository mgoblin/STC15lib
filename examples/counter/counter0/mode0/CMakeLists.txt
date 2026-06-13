add_executable(counter0_mode0_example
    counter0_mode0_example.c
)
add_executable(counter0_mode0_gate_example
    counter0_mode0_gate_example.c
)
add_executable(counter0_mode0_p35_output_example
    counter0_mode0_p35_output_example.c
)

target_link_libraries(counter0_mode0_example PRIVATE stc15hal) 
target_link_libraries(counter0_mode0_gate_example PRIVATE stc15hal) 
target_link_libraries(counter0_mode0_p35_output_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(counter0_mode0_example)
# Transform firmware ihx to hex
ihx_to_hex(counter0_mode0_gate_example)
# Transform firmware ihx to hex
ihx_to_hex(counter0_mode0_p35_output_example)


# upload firmware to STC MCU
add_custom_target(flash_counter0_mode0
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/counter/counter0/mode0/counter0_mode0_example.hex
    DEPENDS counter0_mode0_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL    
)
# upload firmware to STC MCU
add_custom_target(flash_counter0_mode0_gate
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/counter/counter0/mode0/counter0_mode0_gate_example.hex
    DEPENDS counter0_mode0_gate_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_counter0_mode0_p35_output
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/counter/counter0/mode0/counter0_mode0_p35_output_example.hex
    DEPENDS counter0_mode0_p35_output_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

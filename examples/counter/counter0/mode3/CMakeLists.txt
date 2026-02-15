add_executable(counter0_mode3_example
    counter0_mode3_example.c
)
add_executable(counter0_mode3_gate_example
    counter0_mode3_gate_example.c
)
add_executable(counter0_mode3_p35_output_example
    counter0_mode3_p35_output_example.c
)

target_link_libraries(counter0_mode3_example PRIVATE stc15lib)
target_link_libraries(counter0_mode3_gate_example PRIVATE stc15lib)
target_link_libraries(counter0_mode3_p35_output_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(counter0_mode3_example)
# Transform firmware ihx to hex
ihx_to_hex(counter0_mode3_gate_example)
# Transform firmware ihx to hex
ihx_to_hex(counter0_mode3_p35_output_example)

# upload firmware to STC MCU
add_custom_target(flash_counter0_mode3
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/counter0_mode3_example.hex
    DEPENDS counter0_mode3_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_counter0_mode3_gate
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/counter0_mode3_gate_example.hex
    DEPENDS counter0_mode3_gate_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_counter0_mode3_p35_output
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/counter0_mode3_p35_output_example.hex
    DEPENDS counter0_mode3_p35_output_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
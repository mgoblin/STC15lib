add_executable(reset_example
    reset_example.c
)

target_link_libraries(reset_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(reset_example)

# upload firmware to STC MCU
add_custom_target(flash_reset
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/reset/reset_example.hex
    DEPENDS reset_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

add_executable(chip_id_example
    chip_id_example.c
)

target_link_libraries(chip_id_example PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(chip_id_example)

# upload firmware to STC MCU
add_custom_target(flash_chip_id
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/chip_id/chip_id_example.hex
    DEPENDS chip_id_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

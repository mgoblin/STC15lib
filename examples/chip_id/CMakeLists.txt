add_executable(chip_id_example
    chip_id_example.c
)

target_link_libraries(chip_id_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(chip_id_example)

# upload firmware to STC MCU
add_custom_target(flash_chip_id
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/chip_id_example.hex
    DEPENDS adc_async_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

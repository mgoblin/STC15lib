add_executable(spi_master_example
    spi_master_example.c
)

target_link_libraries(spi_master_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(spi_master_example)

# upload firmware to STC MCU
add_custom_target(flash_spi_master
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/spi/spi_master_example.hex
    DEPENDS spi_master_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

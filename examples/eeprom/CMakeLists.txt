add_executable(eeprom_erase_page_example
    eeprom_erase_page_example.c
)
add_executable(eeprom_read_byte_example
    eeprom_read_byte_example.c
)
add_executable(eeprom_write_byte_example
    eeprom_write_byte_example.c
)

target_link_libraries(eeprom_erase_page_example PRIVATE stc15lib)
target_link_libraries(eeprom_read_byte_example PRIVATE stc15lib)
target_link_libraries(eeprom_write_byte_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(eeprom_erase_page_example)
# Transform firmware ihx to hex
ihx_to_hex(eeprom_read_byte_example)
# Transform firmware ihx to hex
ihx_to_hex(eeprom_write_byte_example)


# upload firmware to STC MCU
add_custom_target(flash_eeprom_erase_page
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/eeprom_erase_page_example.hex
    DEPENDS eeprom_erase_page_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_eeprom_read_byte
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/eeprom_read_byte_example.hex
    DEPENDS eeprom_read_byte_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_eeprom_write_byte
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/eeprom_write_byte_example.hex
    DEPENDS eeprom_write_byte_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

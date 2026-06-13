add_executable(wdt_clear_example
    wdt_clear_example.c
)
add_executable(wdt_flag_example
    wdt_flag_example.c
)
add_executable(wdt_start_example
    wdt_start_example.c
)

target_link_libraries(wdt_clear_example PRIVATE stc15hal)
target_link_libraries(wdt_flag_example PRIVATE stc15hal)
target_link_libraries(wdt_start_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(wdt_clear_example)
# Transform firmware ihx to hex
ihx_to_hex(wdt_flag_example)
# Transform firmware ihx to hex
ihx_to_hex(wdt_start_example)

# upload firmware to STC MCU
add_custom_target(flash_wdt_clear
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/wdt/wdt_clear_example.hex
    DEPENDS wdt_clear_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_wdt_flag
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/wdt/wdt_flag_example.hex
    DEPENDS wdt_flag_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_wdt_start
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/wdt/wdt_start_example.hex
    DEPENDS wdt_start_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

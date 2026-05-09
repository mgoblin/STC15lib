add_executable(idle_example
    idle_example.c
)
add_executable(low_voltage_example
    low_voltage_example.c
)
add_executable(powerdown_example
    powerdown_example.c
)

add_executable(wakeup_seconds_example
    wakeup_seconds_example.c
)

target_link_libraries(idle_example PRIVATE stc15lib)
target_link_libraries(low_voltage_example PRIVATE stc15lib)
target_link_libraries(powerdown_example PRIVATE stc15lib)
target_link_libraries(wakeup_seconds_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(idle_example)
ihx_to_hex(low_voltage_example)
ihx_to_hex(powerdown_example)
ihx_to_hex(wakeup_seconds_example)

# upload firmware to STC MCU
add_custom_target(flash_idle
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/idle_example.hex
    DEPENDS idle_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_low_voltage
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/low_voltage_example.hex
    DEPENDS low_voltage_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_powerdown
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/powerdown_example.hex
    DEPENDS powerdown_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

# upload firmware to STC MCU
add_custom_target(flash_wakeup_seconds_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/power_management/wakeup_seconds_example.hex
    DEPENDS powerdown_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)



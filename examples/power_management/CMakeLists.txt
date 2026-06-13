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

target_link_libraries(idle_example PRIVATE stc15hal)
target_link_libraries(low_voltage_example PRIVATE stc15hal)
target_link_libraries(powerdown_example PRIVATE stc15hal)
target_link_libraries(wakeup_seconds_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(idle_example)
ihx_to_hex(low_voltage_example)
ihx_to_hex(powerdown_example)
ihx_to_hex(wakeup_seconds_example)

# upload firmware to STC MCU
add_custom_target(flash_idle
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/power_management/idle_example.hex
    DEPENDS idle_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_low_voltage
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/power_management/low_voltage_example.hex
    DEPENDS low_voltage_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_powerdown
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/power_management/powerdown_example.hex
    DEPENDS powerdown_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_wakeup_seconds_example
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/power_management/wakeup_seconds_example.hex
    DEPENDS powerdown_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)



add_executable(pin_input_only_init_example
    pin_input_only_init_example.c
)
add_executable(pin_mode_example
    pin_mode_example.c
)
add_executable(pin_open_drain_init_example
    pin_open_drain_init_example.c
)
add_executable(pin_push_pull_init_example
    pin_push_pull_init_example.c
)
add_executable(pin_quasi_bidiretional_init_example
    pin_quasi_bidiretional_init_example.c
)

target_link_libraries(pin_input_only_init_example PRIVATE stc15lib)
target_link_libraries(pin_mode_example PRIVATE stc15lib)
target_link_libraries(pin_open_drain_init_example PRIVATE stc15lib)
target_link_libraries(pin_push_pull_init_example PRIVATE stc15lib)
target_link_libraries(pin_quasi_bidiretional_init_example PRIVATE stc15lib)

# Transform firmware ihx to hex
ihx_to_hex(pin_input_only_init_example)
# Transform firmware ihx to hex
ihx_to_hex(pin_mode_example)
# Transform firmware ihx to hex
ihx_to_hex(pin_open_drain_init_example)
# Transform firmware ihx to hex
ihx_to_hex(pin_push_pull_init_example)
# Transform firmware ihx to hex
ihx_to_hex(pin_quasi_bidiretional_init_example)

# upload firmware to STC MCU
add_custom_target(flash_pin_input_only_init
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/pin_input_only_init_example.hex
    DEPENDS pin_input_only_init_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_pin_mode
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/pin_mode_example.hex
    DEPENDS pin_mode_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_pin_open_drain_init
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/pin_open_drain_init_example.hex
    DEPENDS pin_open_drain_init_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_pin_push_pull_init
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/pin_push_pull_init_example.hex
    DEPENDS pin_push_pull_init_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
# upload firmware to STC MCU
add_custom_target(flash_pin_quasi_bidiretional_init
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/pin_quasi_bidiretional_init_example.hex
    DEPENDS pin_quasi_bidiretional_init_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

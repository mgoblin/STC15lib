add_executable(timer0_common_example
    timer0_common_example.c
)
add_executable(timer2_common_example
    timer2_common_example.c
)


target_link_libraries(timer0_common_example PRIVATE stc15hal)
target_link_libraries(timer2_common_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(timer0_common_example)
# Transform firmware ihx to hex
ihx_to_hex(timer2_common_example)

# upload firmware to STC MCU
add_custom_target(flash_timer0_common
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/common/timer0_common_example.hex
    DEPENDS timer0_common_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

# upload firmware to STC MCU
add_custom_target(flash_timer2_common
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/timer/common/timer2_common_example.hex
    DEPENDS timer2_common_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

add_executable(pca_pwm_example
    pca_pwm_example.c
)
add_executable(pca_timer_example
    pca_timer_example.c
)
add_executable(pca_capture_example
    pca_capture_example.c
)

target_link_libraries(pca_pwm_example PRIVATE stc15hal)
target_link_libraries(pca_timer_example PRIVATE stc15hal)
target_link_libraries(pca_capture_example PRIVATE stc15hal)

# Transform firmware ihx to hex
ihx_to_hex(pca_pwm_example)
ihx_to_hex(pca_timer_example)
ihx_to_hex(pca_capture_example)

# upload firmware to STC MCU
add_custom_target(flash_pca_pwm
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/pca/pca_pwm_example.hex
    DEPENDS pca_pwm_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_pca_timer
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/pca/pca_timer_example.hex
    DEPENDS pca_timer_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)
# upload firmware to STC MCU
add_custom_target(flash_pca_capture
    COMMAND stcgal ${CMAKE_BINARY_DIR}/examples/pca/pca_capture_example.hex
    DEPENDS pca_capture_example
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

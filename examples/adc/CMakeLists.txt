add_executable(adc_async_example
    adc_async_example.c
)

add_executable(adc_read_example
    adc_read_example.c
)

target_link_libraries(adc_read_example PRIVATE stc15lib) 
target_link_libraries(adc_async_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(adc_async_example)
ihx_to_hex(adc_read_example)

# upload firmware to STC MCU
add_custom_target(flash
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/adc_read_example.hex
    DEPENDS adc_async_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
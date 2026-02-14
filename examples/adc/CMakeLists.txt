add_executable(adc_async_example
    adc_async_example.c
)

target_include_directories(adc_async_example 
    PRIVATE "${CMAKE_SOURCE_DIR}/include"
)

target_compile_options(adc_async_example PRIVATE
  $<IF:$<COMPILE_LANGUAGE:C>, -mmcs51 --model-small --std-c23 --debug --no-xinit-opt --opt-code-size,>
  $<IF:$<COMPILE_LANGUAGE:ASM>, -plosgff,>
)

target_link_options(adc_async_example PRIVATE
  -mmcs51 --debug
)

# Transform firmware ihx to hex
ihx_to_hex(adc_async_example)

# upload firmware to STC MCU
add_custom_target(flash
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/adc_read_example.hex
    DEPENDS adc_async_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)
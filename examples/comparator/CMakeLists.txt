add_executable(comparator_async_example
    comparator_async_example.c
)

target_link_libraries(comparator_async_example PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(comparator_async_example)

# upload firmware to STC MCU
add_custom_target(flash_comparator_async
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/comparator_async_example.hex
    DEPENDS comparator_async_example
    JOB_POOL console # for ninja build tool output stgal command input to console
)

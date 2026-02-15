add_executable(mem_dump
    mem_dump.c
)

target_link_libraries(mem_dump PRIVATE stc15lib) 

# Transform firmware ihx to hex
ihx_to_hex(mem_dump)

# upload firmware to STC MCU
add_custom_target(flash_mem_dump
    COMMAND stcgal ${CMAKE_BINARY_DIR}/src/mem_dump.hex
    DEPENDS mem_dump
    JOB_POOL console # for ninja build tool output stgal command input to console
)

add_executable(mem_dump
    mem_dump.c
    mem_print.c
)

target_link_libraries(mem_dump PRIVATE stc15hal) 

# Transform firmware ihx to hex
ihx_to_hex(mem_dump)

# upload firmware to STC MCU
add_custom_target(flash_mem_dump
    COMMAND stcgal ${CMAKE_BINARY_DIR}/utils/memory_dumper/mem_dump.hex
    DEPENDS mem_dump
    COMMENT "Waiting for MCU, please cycle power:"
    USES_TERMINAL
)

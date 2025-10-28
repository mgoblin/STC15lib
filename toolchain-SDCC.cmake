# the name of the target operating system
set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_ASM_COMPILER_ID "SDAS8051")

# which compilers to use for C
set(CMAKE_C_COMPILER sdcc CACHE INTERNAL "SDCC C compiler")
set(CMAKE_ASM_COMPILER sdas8051 CACHE INTERNAL "asm compiler")
set(CMAKE_ASM_COMPILER_LINKER sdld CACHE INTERNAL "asm linker tool")
set(CMAKE_C_COMPILER_LINKER sdld CACHE INTERNAL "c linker tool")
set(CMAKE_OBJCOPY sdobjcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_PACKIHX packihx CACHE INTERNAL "packihx tool")
set(CMAKE_MAKEBIN makebin CACHE INTERNAL "makebin tool")

get_filename_component(SDCC_LOCATION "${CMAKE_ASM_COMPILER}" PATH)
get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER}" PATH)
get_filename_component(SDCC_LOCATION "${CMAKE_ASM_COMPILER_LINKER}" PATH)
get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER_LINKER}" PATH)
find_program(SDCCLIB_EXECUTABLE sdar PATHS "${SDCC_LOCATION}" NO_DEFAULT_PATH)
find_program(SDCCLIB_EXECUTABLE sdar)
set(CMAKE_AR "${SDCCLIB_EXECUTABLE}" CACHE FILEPATH "The sdcc librarian" FORCE)

# Compilation flags
set(CMAKE_C_FLAGS "-mmcs51 --model-small --std-c23")
set(CMAKE_ASM_FLAGS "-lso -a -y")
set(CMAKE_ASM_LINK_FLAGS "-niumwx -M -y")

# here is the target environment is located
set(CMAKE_FIND_ROOT_PATH  /usr/share/sdcc)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

function(ihx_to_hex bin)
    add_custom_command( 
        TARGET ${bin} POST_BUILD COMMAND  ${CMAKE_PACKIHX} ${bin}.ihx > ${bin}.hex
        TARGET ${bin} POST_BUILD COMMAND  ${CMAKE_MAKEBIN} -p ${bin}.ihx ${bin}.bin
        TARGET ${bin} POST_BUILD COMMAND  echo -n "Firmware bytes size: "
        TARGET ${bin} POST_BUILD COMMAND  stat --format '%s' ${bin}.bin
    )
endfunction(ihx_to_hex)

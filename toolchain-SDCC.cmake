set(CMAKE_SYSTEM_NAME Generic)

set(CMAKE_CROSSCOMPILING TRUE)
set(CMAKE_ASM_COMPILER_ID "SDAS8051") 
set(CMAKE_C_COMPILER_WORKS TRUE)

set(CMAKE_C_COMPILER sdcc CACHE INTERNAL "c language compiler")
set(CMAKE_ASM_COMPILER sdas8051 CACHE INTERNAL "asm compiler")
set(CMAKE_ASM_COMPILER_LINKER sdld CACHE INTERNAL "asm linker tool")
set(CMAKE_OBJCOPY sdobjcopy CACHE INTERNAL "objcopy tool")
set(CMAKE_PACKIHX packihx CACHE INTERNAL "packihx tool")

get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER}" PATH)
get_filename_component(SDCC_LOCATION "${CMAKE_ASM_COMPILER}" PATH)
get_filename_component(SDCC_LOCATION "${CMAKE_ASM_COMPILER_LINKER}" PATH)
find_program(SDCCLIB_EXECUTABLE sdar PATHS "${SDCC_LOCATION}" NO_DEFAULT_PATH)
find_program(SDCCLIB_EXECUTABLE sdar)
set(CMAKE_AR "${SDCCLIB_EXECUTABLE}" CACHE FILEPATH "The sdcc librarian" FORCE)

function(ihx_to_hex bin)
    add_custom_command( 
        TARGET ${bin} POST_BUILD COMMAND  ${CMAKE_PACKIHX} ${bin}.ihx > ${bin}.hex
        TARGET ${bin} POST_BUILD COMMAND  makebin -p ${bin}.hex ${bin}.bin
        TARGET ${bin} POST_BUILD COMMAND  stat --format 'hex size: %s bytes' ${bin}.bin
    )
endfunction(ihx_to_hex)


# here is the target environment is located
set(CMAKE_FIND_ROOT_PATH  /usr/share/sdcc)

# adjust the default behaviour of the FIND_XXX() commands:
# search headers and libraries in the target environment, search 
# programs in the host environment
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
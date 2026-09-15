# 1. Указываем целевую систему. Это заставит CMake использовать Generic-SDCC-C.cmake
set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR mcs51)

set(CMAKE_ASM_COMPILER_ID "SDAS8051")

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)

set(SDCC_DIR /usr/bin)
set(SDCC_ROOT /usr/share/sdcc) # В Debian заголовки обычно лежат здесь

set(CMAKE_C_COMPILER ${SDCC_DIR}/sdcc)
set(CMAKE_CXX_COMPILER ${SDCC_DIR}/sdcc)
set(CMAKE_PACKIHX packihx CACHE INTERNAL "packihx tool")
set(CMAKE_MAKEBIN makebin CACHE INTERNAL "makebin tool")

set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)
set(CMAKE_EXECUTABLE_SUFFIX ".ihx")
set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")

# Compilation flags
set(CMAKE_C_FLAGS_INIT "-mmcs51 --model-small --std-c23 --Werror")
set(SDCC_MCS51_MEMORY_FLAGS "--model-small --iram-size 256 --xram-size 256 --code-size 8096")


# --- Static Library config ---

# 1. Use dsar as the archiver for SDCC. We need to find it first. It is usually located next to the compiler, but we can also search in the system PATH.
GET_FILENAME_COMPONENT(SDCC_LOCATION "${CMAKE_C_COMPILER}" PATH)
FIND_PROGRAM(SDCCLIB_EXECUTABLE sdar PATHS "${SDCC_LOCATION}" NO_DEFAULT_PATH)
# If not found, try to find it in the system PATH
FIND_PROGRAM(SDCCLIB_EXECUTABLE sdar)

# Use sdar 
SET(CMAKE_AR "${SDCCLIB_EXECUTABLE}" CACHE FILEPATH "The sdcc librarian (sdar)" FORCE)

# 2. Set the command to create static libraries using sdar
SET(CMAKE_C_CREATE_STATIC_LIBRARY
    "<CMAKE_AR> -rc <TARGET> <OBJECTS>")

# 3. Set the command to link static libraries using sdcc
SET(CMAKE_C_LINK_EXECUTABLE 
    "<CMAKE_C_COMPILER> <FLAGS> <OBJECTS> --model-small --out-fmt-ihx -o <TARGET> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>"
)

set(CMAKE_FIND_ROOT_PATH ${SDCC_ROOT})
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)

find_package(Python3 REQUIRED COMPONENTS Interpreter)
if (Python3_FOUND)
    message(STATUS "Python interpreter found: ${Python3_EXECUTABLE}")
else()
    message(FATAL_ERROR "Python interpreter not found. Please install Python3.")
endif()

function(ihx_to_hex bin)
    add_custom_command( 
        TARGET ${bin} 
        POST_BUILD 
        COMMAND  ${CMAKE_PACKIHX} ${bin}.ihx > ${bin}.hex 2>/dev/null
        COMMAND ${Python3_EXECUTABLE} "${PROJECT_SOURCE_DIR}/size.py" "${CMAKE_CURRENT_BINARY_DIR}/${bin}.mem" "${bin}"
    )
endfunction(ihx_to_hex)
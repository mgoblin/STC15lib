# This file implements basic support for sdcc (http://sdcc.sourceforge.net/)
# a free C compiler for 8 and 16 bit microcontrollers.
# To use it either a toolchain file is required or cmake has to be run like this:
# cmake -DCMAKE_C_COMPILER=sdcc -DCMAKE_SYSTEM_NAME=Generic <dir...>
# Since sdcc doesn't support C++, C++ support should be disabled in the
# CMakeLists.txt using the project() command:
# project(my_project C)

set(CMAKE_STATIC_LIBRARY_PREFIX "")
set(CMAKE_STATIC_LIBRARY_SUFFIX ".lib")
set(CMAKE_SHARED_LIBRARY_PREFIX "")          # lib
set(CMAKE_SHARED_LIBRARY_SUFFIX ".lib")      # .so
set(CMAKE_IMPORT_LIBRARY_PREFIX )
set(CMAKE_IMPORT_LIBRARY_SUFFIX )
set(CMAKE_EXECUTABLE_SUFFIX ".ihx")          # intel hex file
set(CMAKE_LINK_LIBRARY_SUFFIX ".lib")
set(CMAKE_DL_LIBS "")

set(CMAKE_C_OUTPUT_EXTENSION ".rel")

# find sdar/sdcclib as CMAKE_AR
# since cmake may already have searched for "ar", sdar has to
# be searched with a different variable name (SDCCAR_EXECUTABLE)
# and must then be forced into the cache.
# sdcclib has been deprecated in SDCC 3.2.0 and removed in 3.8.6
# so we first look for sdar
get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER}" PATH)
find_program(SDCCAR_EXECUTABLE sdar NAMES sdar PATHS "${SDCC_LOCATION}" NO_DEFAULT_PATH)
find_program(SDCCAR_EXECUTABLE sdar NAMES sdar)

if("${SDCCAR_EXECUTABLE}" MATCHES "sdar")
  set(CMAKE_AR_OPTIONS "-a")
else()
  set(CMAKE_AR_OPTIONS "-rc")
endif()

set(CMAKE_C_LINKER_WRAPPER_FLAG "-Wl" ",")

if(NOT DEFINED CMAKE_C_FLAGS_INIT)
    set(CMAKE_C_FLAGS_INIT "")
endif()

if(NOT DEFINED CMAKE_ASM_FLAGS_INIT)
    set(CMAKE_ASM_FLAGS_INIT "")
endif()

set(CMAKE_ASM_FLAGS "-lso")

if(NOT DEFINED CMAKE_EXE_LINKER_FLAGS_INIT)
    set (CMAKE_EXE_LINKER_FLAGS_INIT "")
endif()

set(CMAKE_ASM_LINK_FLAGS "-niumwx")


set(CMAKE_C_COMPILE_OBJECT  "<CMAKE_C_COMPILER> <DEFINES> <INCLUDES> <FLAGS> <CMAKE_C_FLAGS> -o <OBJECT> -c <SOURCE>")
set(CMAKE_C_LINK_EXECUTABLE "<CMAKE_C_COMPILER> <FLAGS> <OBJECTS> --out-fmt-ihx -o  <TARGET> <CMAKE_C_LINK_FLAGS> <LINK_FLAGS> <LINK_LIBRARIES>")
set(CMAKE_ASM_COMPILE_OBJECT  "<CMAKE_ASM_COMPILER> <FLAGS> <OBJECT> <SOURCE>")
set(CMAKE_ASM_LINK_EXECUTABLE "${CMAKE_ASM_LINKER} <CMAKE_ASM_LINK_FLAGS> <TARGET> <OBJECTS>")


set(CMAKE_C_CREATE_STATIC_LIBRARY
        "\"${CMAKE_COMMAND}\" -E remove <TARGET>"
        "<CMAKE_AR> -r <TARGET> <LINK_FLAGS> <OBJECTS> ")

set(CMAKE_C_CREATE_SHARED_LIBRARY "")
set(CMAKE_C_CREATE_MODULE_LIBRARY "")


set(CMAKE_C_OUTPUT_EXTENSION ".rel")
set(CMAKE_C_OUTPUT_EXTENSION_REPLACE 1)

# find sdar/sdcclib as CMAKE_AR
# since cmake may already have searched for "ar", sdar has to
# be searched with a different variable name (SDCCAR_EXECUTABLE)
# and must then be forced into the cache.
# sdcclib has been deprecated in SDCC 3.2.0 and removed in 3.8.6
# so we first look for sdar
get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER}" PATH)
get_filename_component(SDCC_LOCATION "${CMAKE_C_COMPILER_LINKER}" PATH)
find_program(SDCCAR_EXECUTABLE sdar NAMES sdcclib PATHS "${SDCC_LOCATION}" NO_DEFAULT_PATH)
find_program(SDCCAR_EXECUTABLE sdar NAMES sdcclib)
# for compatibility, in case SDCCLIB_EXECUTABLE is set, we use it
if(DEFINED SDCCLIB_EXECUTABLE)
  set(CMAKE_AR "${SDCCLIB_EXECUTABLE}" CACHE FILEPATH "The sdcc librarian" FORCE)
else()
  set(CMAKE_AR "${SDCCAR_EXECUTABLE}" CACHE FILEPATH "The sdcc librarian" FORCE)
endif()

if("${SDCCAR_EXECUTABLE}" MATCHES "sdcclib")
  set(CMAKE_AR_OPTIONS "-a")
else()
  set(CMAKE_AR_OPTIONS "-rc")
endif()

# needs sdcc + sdar/sdcclib
set(CMAKE_C_CREATE_STATIC_LIBRARY
      "\"${CMAKE_COMMAND}\" -E remove <TARGET>"
      "<CMAKE_AR> ${CMAKE_AR_OPTIONS} <TARGET> <LINK_FLAGS> <OBJECTS> ")

# not supported by sdcc
set(CMAKE_C_CREATE_SHARED_LIBRARY "")
set(CMAKE_C_CREATE_MODULE_LIBRARY "")


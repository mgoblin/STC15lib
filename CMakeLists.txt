cmake_minimum_required(VERSION 3.31) # Specify minimum CMake version

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

file(REAL_PATH "toolchain-SDCC.cmake" CMAKE_TOOLCHAIN_FILE EXPAND_TILDE)

project(
    stc15hal
    VERSION 0.17.0
    LANGUAGES C ASM
) # Define project name and language

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# add headers to stc15hal
include_directories(stc15hal 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include # For public headers during build
)

add_subdirectory("src")
add_subdirectory("examples")
add_subdirectory("utils")

find_package(Doxygen REQUIRED dot)
if(Doxygen_FOUND)
  message(STATUS "Found Doxygen Version "
    "${DOXYGEN_VERSION} at ${DOXYGEN_EXECUTABLE}")
  
  add_custom_target(docs ALL
    COMMAND doxygen doxygen.conf
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
    COMMENT "Generating project documentation"
  )
else()
  message(STATUS "Doxygen not found. Docs generation disabled")
endif()

# Build a list of `cat` commands for each file in mem_list.txt
# We'll read the file at build time and cat each path listed
set(EXAMPLES_BUILD_SUMMART_CMD "")

list(APPEND EXAMPLES_BUILD_SUMMART_CMD
  COMMAND 
  ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_examples_build_summary.py 
  "${CMAKE_BINARY_DIR}/examples"
  "${CMAKE_BINARY_DIR}/build_summary.txt"
)

# Add a custom target that runs *after all* targets and generates a summary of .hex files and their sizes
add_custom_target(make_build_summary ALL
  COMMENT "Display example .hex files and their sizes (post-build step)"
  ${EXAMPLES_BUILD_SUMMART_CMD}
)

# Add a custom target that runs *after all* targets and generates a summary of .hex files and their sizes
add_custom_target(print_build_summary ALL
  COMMAND ${CMAKE_COMMAND} -E cat "${CMAKE_BINARY_DIR}/build_summary.txt"
  COMMENT "Printing contents of ${CMAKE_BINARY_DIR}/build_summary.txt:"
  VERBATIM
)

add_dependencies(make_build_summary mem_dump)
add_dependencies(print_build_summary make_build_summary)
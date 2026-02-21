cmake_minimum_required(VERSION 3.31) # Specify minimum CMake version

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

file(REAL_PATH "toolchain-SDCC.cmake" CMAKE_TOOLCHAIN_FILE EXPAND_TILDE)

project(
    stc15lib
    VERSION 0.15.0
    LANGUAGES C ASM
) # Define project name and language

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)

# add headers to stc15lib
include_directories(stc15lib 
  PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include # For public headers during build
)

add_subdirectory("src")
add_subdirectory("examples")

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



cmake_minimum_required(VERSION 3.31) # Specify minimum CMake version

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

file(REAL_PATH "toolchain-SDCC.cmake" CMAKE_TOOLCHAIN_FILE EXPAND_TILDE)

project(stc15lib LANGUAGES C ASM) # Define project name and language

set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED ON)


add_subdirectory("src")



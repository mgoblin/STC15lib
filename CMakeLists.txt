cmake_minimum_required(VERSION 3.31) # Specify minimum CMake version

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_SOURCE_DIR}/8051-toolchain.cmake")

project(stc15lib C ASM) # Define project name and language

add_subdirectory("src")


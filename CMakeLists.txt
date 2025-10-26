cmake_minimum_required(VERSION 3.31) # Specify minimum CMake version

set(CMAKE_TOOLCHAIN_FILE "toolchain-SDCC.cmake")

project(stc15lib C) # Define project name and language

add_subdirectory("src")


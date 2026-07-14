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

# Collect all currently added targets in all subdirectories
# Returns each target as: "relative_dir_path/target_name"
# Example: ["blink", "subdir1/uart", "subdir2/flash_app"]
function(get_all_targets_mem _result _dir)
    # Compute relative path from CMAKE_CURRENT_LIST_DIR to current _dir
    file(RELATIVE_PATH _rel_dir "${CMAKE_CURRENT_LIST_DIR}" "${_dir}")

    # Normalize prefix: empty for root, "subdir/" for nested
    if(_rel_dir STREQUAL "." OR _rel_dir STREQUAL "")
        set(_prefix "")
    else()
        set(_prefix "${_rel_dir}/")
    endif()

    # Recurse into subdirectories
    get_property(_subdirs DIRECTORY "${_dir}" PROPERTY SUBDIRECTORIES)
    foreach(_subdir IN LISTS _subdirs)
        get_all_targets_mem(${_result} "${_subdir}")
    endforeach()

    # Collect targets in this directory, prefixed with relative path
    get_directory_property(_sub_targets DIRECTORY "${_dir}" BUILDSYSTEM_TARGETS)
    foreach(_target IN LISTS _sub_targets)
        # Only append if not already in list (avoid duplicates from overlapping calls)
        get_target_property(_type ${_target} TYPE)
        if(_type STREQUAL "EXECUTABLE")
          list(APPEND ${_result} "${CMAKE_BINARY_DIR}/${_prefix}${_target}.mem")
        endif()  
    endforeach()

    # Ensure parent scope gets the full list (CMake lists are passed by name)
    set(${_result} ${${_result}} PARENT_SCOPE)
endfunction()

get_all_targets_mem(ALL_MEM_FILES ${CMAKE_CURRENT_LIST_DIR}/examples)
file(WRITE "${CMAKE_BINARY_DIR}/mem_list.txt" "${ALL_MEM_FILES}\n")

# Build a list of `cat` commands for each file in mem_list.txt
# We'll read the file at build time and cat each path listed
set(EXAMPLES_BUILD_SUMMART_CMD "")

list(APPEND EXAMPLES_BUILD_SUMMART_CMD
    COMMAND ${Python3_EXECUTABLE} ${CMAKE_CURRENT_SOURCE_DIR}/cmake_examples_build_summary.py "${CMAKE_BINARY_DIR}/mem_list.txt"
)

# Add a custom target that runs *after all* targets, with a clean dependency chain
add_custom_target(build_summary ALL
    COMMENT "Display example .hex files and their sizes (post-build step)"
    ${EXAMPLES_BUILD_SUMMART_CMD}
)

add_dependencies(build_summary mem_dump)
# Host tests for the library headers.
#
# The rest of this project is cross compiled for the 8051 with SDCC, but the
# tests in this directory run on the build host. They verify the pure logic of
# the HAL headers (bit masks, shifts, token pasting, enum encodings) by
# compiling the real headers against a host stub for the SDCC <compiler.h>,
# then asserting on the register values the macros produce.
#
# A custom command is used instead of add_executable on purpose: the parent
# project sets CMAKE_C_COMPILER to SDCC, so an ordinary target here would be
# cross compiled into an mcs51 binary that cannot run on the build host. The
# custom command invokes the host compiler directly and leaves the SDCC
# toolchain untouched.
#
# Add a new test by appending its name to HOST_TESTS; the source is expected at
# <name>.c in this directory.

set(HOST_TESTS
    test_pca
    test_spi
)

find_program(HOST_CC NAMES cc gcc clang)

if(NOT HOST_CC)
    message(WARNING "No host C compiler found, host tests will not be built")
    return()
endif()

set(HOST_TEST_BIN_DIR ${CMAKE_BINARY_DIR}/test)

file(MAKE_DIRECTORY ${HOST_TEST_BIN_DIR})

add_custom_target(host_tests ALL
    COMMENT "Building host tests"
)

foreach(test IN LISTS HOST_TESTS)
    set(test_source ${CMAKE_CURRENT_SOURCE_DIR}/${test}.c)
    set(test_binary ${HOST_TEST_BIN_DIR}/${test})

    add_custom_command(
        OUTPUT ${test_binary}
        COMMAND ${HOST_CC}
                -std=c23 -Wall -Wextra
                -I ${CMAKE_CURRENT_SOURCE_DIR}/stubs
                -I ${CMAKE_SOURCE_DIR}/include
                -o ${test_binary}
                ${test_source}
        DEPENDS ${test_source}
                ${CMAKE_CURRENT_SOURCE_DIR}/stubs/compiler.h
        COMMENT "Building host test ${test}"
        VERBATIM
    )

    add_custom_target(${test}_build ALL DEPENDS ${test_binary})

    add_dependencies(host_tests ${test}_build)

    add_test(
        NAME ${test}
        COMMAND ${test_binary}
    )
endforeach()

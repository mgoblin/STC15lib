add_subdirectory("adc")
add_subdirectory("bits")
add_subdirectory("chip_id")
add_subdirectory("comparator")
add_subdirectory("counter")
add_subdirectory("delay")
add_subdirectory("eeprom")
add_subdirectory("frequency")
add_subdirectory("interrupt")
add_subdirectory("gpio")
add_subdirectory("power_management")
add_subdirectory("reset")
add_subdirectory("timer")
add_subdirectory("uart")
add_subdirectory("wdt")

# Build summary: generate and print a summary of example .hex files and sizes
set(EXAMPLES_BUILD_SUMMARY_CMD "")

list(APPEND EXAMPLES_BUILD_SUMMARY_CMD
	COMMAND
	${Python3_EXECUTABLE} ${CMAKE_SOURCE_DIR}/cmake_examples_build_summary.py
	"${CMAKE_BINARY_DIR}/examples"
	"${CMAKE_BINARY_DIR}/examples/build_summary.txt"
)

add_custom_target(make_build_summary ALL
	COMMENT "Display example .hex files and their sizes (post-build step)"
	${EXAMPLES_BUILD_SUMMARY_CMD}
)

add_custom_target(print_build_summary ALL
	COMMAND ${CMAKE_COMMAND} -E cat "${CMAKE_BINARY_DIR}/examples/build_summary.txt"
	COMMENT "Printing contents of ${CMAKE_BINARY_DIR}/examples/build_summary.txt:"
	VERBATIM
)

add_dependencies(make_build_summary mem_dump)
add_dependencies(print_build_summary make_build_summary)
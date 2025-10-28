add_library(stc15lib STATIC
  uart.c
) # Create libray from uart.c

# add headers to stc15lib
target_include_directories(stc15lib 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # For public headers during build
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # For public headers after installation
)

install(
  TARGETS stc15lib
  EXPORT stc15libTargets
  LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
  ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
  RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
  INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
)

install(
  DIRECTORY include/
  DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
)

install(EXPORT stc15libTargets
    NAMESPACE stc15lib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stc15lib
    FILE stc15libTargets.cmake
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "stc15libConfigVersion.cmake"
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
    "${CMAKE_CURRENT_LIST_DIR}/cmake/stc15libConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/stc15libConfig.cmake"
    INSTALL_DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/stc15lib
)

install(
    EXPORT stc15libTargets
    FILE stc15libTargets.cmake
    NAMESPACE stc15lib::
    DESTINATION ${CMAKE_INSTALL_DATAROOTDIR}/cmake/stc15lib
)



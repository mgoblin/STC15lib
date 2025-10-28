add_library(stc15lib STATIC
  uart.c
) # Create libray from uart.c

# add headers to stc15lib
target_include_directories(stc15lib 
  PUBLIC
    $<BUILD_INTERFACE:${CMAKE_SOURCE_DIR}/include> # For public headers during build
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}> # For public headers after installation
)

install(TARGETS stc15lib
    EXPORT stc15libTargets
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
)

install(DIRECTORY include/
    DESTINATION "${CMAKE_INSTALL_INCLUDEDIR}"
    FILES_MATCHING PATTERN "*.h"
)

install(EXPORT stc15libTargets
    NAMESPACE stc15lib::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/stc15lib
    FILE stc15libTargets.cmake
)
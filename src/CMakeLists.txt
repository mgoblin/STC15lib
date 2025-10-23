add_library(stc15lib STATIC
  uart.c
) # Create libray from uart.c

# add headers to stc15lib
target_include_directories(stc15lib PUBLIC
    ../include
)

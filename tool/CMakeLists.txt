cmake_minimum_required (VERSION 2.6)
project (ccrwrom)

# The version number.
set (CCWR_VERSION_MAJOR 1)
set (CCWR_VERSION_MINOR 0)

configure_file (
  "${PROJECT_SOURCE_DIR}/Config.h.in"
  "${PROJECT_BINARY_DIR}/src/Config.h"
)

add_executable(ccrwrom src/Command.cpp src/debug.cpp src/main.cpp rom_tools.cpp romdb.cpp test.cpp usb.cpp)
target_link_libraries (ccrwrom MathFunctions)
cmake_minimum_required(VERSION 3.30)
project(kaleidoscope)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define variable for examples location.
set(KALEIDOSCOPE_EXAMPLES_DIR "${CMAKE_SOURCE_DIR}/examples")
add_definitions( -DKALEIDOSCOPE_EXAMPLES_DIR="${KALEIDOSCOPE_EXAMPLES_DIR}")

add_executable(kaleidoscope main.cpp)

# Add the subdirectories.
add_subdirectory(src)

# Link the libraries.
target_link_libraries(kaleidoscope PUBLIC lexer)
target_link_libraries(kaleidoscope PUBLIC parser)
target_link_libraries(kaleidoscope PUBLIC repl)
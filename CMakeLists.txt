cmake_minimum_required(VERSION 3.30)
project(kaleidoscope)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define variable for examples location.
set(KALEIDOSCOPE_EXAMPLES_DIR ".${CMAKE_SOURCES_DIR}/examples")
add_definitions( -DKALEIDOSCOPE_EXAMPLES_DIR="${KALEIDOSCOPE_EXAMPLES_DIR}")

add_executable(kaleidoscope main.cpp)

# Add the lexer.
add_subdirectory(lexer)
target_link_libraries(kaleidoscope PUBLIC lexer)
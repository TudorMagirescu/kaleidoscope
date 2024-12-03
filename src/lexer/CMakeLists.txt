file(GLOB HEADERS_LIST "${CMAKE_SOURCE_DIR}/include/lexer/*.h")
file(GLOB SOURCES_LIST "${CMAKE_SOURCE_DIR}/src/lexer/*.cpp")

add_library(lexer ${HEADERS_LIST} ${SOURCES_LIST})

target_include_directories(lexer PUBLIC ${CMAKE_SOURCE_DIR}/include)
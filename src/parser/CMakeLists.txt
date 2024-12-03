file(GLOB HEADERS_LIST "${CMAKE_SOURCE_DIR}/include/parser/*.h")
file(GLOB SOURCES_LIST "${CMAKE_SOURCE_DIR}/src/parser/*.cpp")

add_library(parser ${HEADERS_LIST} ${SOURCES_LIST})

target_include_directories(parser PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(parser PUBLIC lexer)
file(GLOB HEADERS_LIST "${CMAKE_SOURCE_DIR}/include/repl/*.h")
file(GLOB SOURCES_LIST "${CMAKE_SOURCE_DIR}/src/repl/*.cpp")

add_library(repl ${HEADERS_LIST} ${SOURCES_LIST})

target_include_directories(repl PUBLIC ${CMAKE_SOURCE_DIR}/include)

target_link_libraries(repl PUBLIC parser)
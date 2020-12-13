if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(colang)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -w")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

include_directories(. compiler ast parser lib internal gc)

add_subdirectory(ast)
add_subdirectory(compiler)
add_subdirectory(parser)
add_subdirectory(lib)
add_subdirectory(internal)
add_subdirectory(gc)

add_executable(colang colang.cpp)

target_link_libraries(colang parser compiler ast lib -lstdc++fs)
if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(do)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -w")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

include_directories(. asm ast parser lib internal gc)

add_subdirectory(ast)
add_subdirectory(asm)
add_subdirectory(parser)
add_subdirectory(lib)
add_subdirectory(internal)
add_subdirectory(gc)

add_executable(do do.cpp)

target_link_libraries(do parser asm ast lib -lstdc++fs)
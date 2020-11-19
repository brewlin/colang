if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(do)

add_definitions("-g -Wall -std=c++17 ")

include_directories(. asm ast parser pkg runtime)

add_subdirectory(ast)
add_subdirectory(asm)
add_subdirectory(runtime)
add_subdirectory(parser)
add_subdirectory(pkg)
add_subdirectory(internal)

add_executable(do do.cpp)

target_link_libraries(do parser asm ast runtime pkg -lstdc++fs)
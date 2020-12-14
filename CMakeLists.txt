if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(colang)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -w")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

# compiler
include_directories(. compiler src/ast src/parser src/lib src/internal src/gc)
add_subdirectory(compiler)
add_subdirectory(src/ast)
add_subdirectory(src/parser)
add_subdirectory(src/lib)
add_subdirectory(src/internal)
add_subdirectory(src/gc)
add_executable(colang colang.cpp)
target_link_libraries(colang parser compiler ast lib -lstdc++fs)

# asmer
include_directories(. src/asm_ast src/asm_parser src/lib )
add_subdirectory(src/asm_parser)
add_executable(asmer asmer.cpp)
target_link_libraries(asmer asm_parser lib -lstdc++fs)

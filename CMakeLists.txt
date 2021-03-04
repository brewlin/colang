if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(colang)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -w")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

# compiler
include_directories(. compiler compiler/ast compiler/parser lib internal gc)
add_subdirectory(compiler)
add_subdirectory(compiler/ast)
add_subdirectory(compiler/parser)
add_subdirectory(lib)
add_subdirectory(internal)
add_subdirectory(gc)
add_executable(co-compiler compiler.cpp)
target_link_libraries(co-compiler co_parser compiler co_ast lib -lstdc++fs)

# asmer
include_directories(. asmer asmer/ast asmer/parser asmer/instruct lib)
add_subdirectory(asmer/parser)
add_subdirectory(asmer/ast)
add_subdirectory(asmer/instruct)
add_subdirectory(asmer)
add_executable(co-asmer asmer.cpp)
target_link_libraries(co-asmer  asmer asm_parser asmer asm_instruct asm_ast lib -lstdc++fs)

# linker
include_directories(. linker lib)
add_subdirectory(crt)
add_subdirectory(linker)
add_executable(co-linker linker.cpp)
target_link_libraries(co-linker  linker lib -lstdc++fs)

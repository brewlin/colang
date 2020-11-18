if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(do)
set(CMAKE_CXX_COMPILER "clang++")
SET (CMAKE_AR      "llvm-ar")
SET (CMAKE_LINKER  "llvm-ld")
SET (CMAKE_NM      "llvm-nm")
SET (CMAKE_OBJDUMP "llvm-objdump")
SET (CMAKE_RANLIB  "llvm-ranlib")
# llvm-config --ldflags --libs
execute_process(COMMAND llvm-config --ldflags --libs OUTPUT_VARIABLE LLVMLD_CONFIG)
string(REGEX REPLACE "\n" " " LLVMLD_CONFIG "${LLVMLD_CONFIG}")
SET (CMAKE_EXE_LINKER_FLAGS  ${LLVMLD_CONFIG} )

find_package(LLVM REQUIRED CONFIG)
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})
add_definitions("-g -std=c++17")
include_directories(. asm ast parser pkg runtime llvm )


add_subdirectory(ast)
add_subdirectory(asm)
add_subdirectory(llvm)
add_subdirectory(runtime)
add_subdirectory(parser)
add_subdirectory(pkg)
add_subdirectory(internal)

add_executable(do do.cpp)

# that we wish to use
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Link against LLVM libraries
# 越基础的库就要越放后面，保证链接正常
target_link_libraries(
        do
        parser
        asm
        llvm
        ast
        runtime
        pkg
        ${llvm_libs}
)
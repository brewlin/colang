if(COMMAND cmake_policy)
    cmake_policy(SET CMP0003 NEW)
endif(COMMAND cmake_policy)
cmake_minimum_required(VERSION 3.10)

project(colang)

set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -w")

set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -g")

# compiler
include_directories(. compiler compiler/asm compiler/gen compiler/internal  compiler/ast compiler/parser lib internal gc)
add_subdirectory(compiler/asm)
add_subdirectory(compiler/gen)
add_subdirectory(compiler/internal)
add_subdirectory(compiler/ast)
add_subdirectory(compiler/parser)
add_subdirectory(lib)
add_subdirectory(internal)
add_subdirectory(gc)
add_executable(co compiler/compiler.cpp)
target_link_libraries(co co_parser co_gen co_internal co_asm co_gen co_asm co_ast lib -lstdc++fs)

# asmer
include_directories(. asmer asmer/asmer asmer/ast asmer/parser asmer/instruct asmer/elf lib)
add_subdirectory(asmer/parser)
add_subdirectory(asmer/ast)
add_subdirectory(asmer/instruct)
add_subdirectory(asmer/elf)
add_subdirectory(asmer/asmer)
add_executable(cas asmer/asmer.cpp)
target_link_libraries(cas  asm_asmer asm_parser asm_elf asm_asmer asm_instruct asm_ast lib -lstdc++fs)

# linker
include_directories(. linker lib)
add_subdirectory(crt)
add_subdirectory(linker/link)
add_subdirectory(linker/elf)
add_executable(cld linker/linker.cpp)
target_link_libraries(cld  linker link_elf lib -lstdc++fs)


# runtime
include_directories(runtime/net/include)
add_subdirectory(runtime/net/core)
add_subdirectory(runtime/net/event)
add_subdirectory(runtime/net/http)

#install
install(TARGETS co cas cld
        RUNTIME DESTINATION bin)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/runtime/pkg/"
        DESTINATION lib/copkg)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/runtime/internal/"
        DESTINATION lib/coasm)
install(DIRECTORY "${CMAKE_SOURCE_DIR}/runtime/syscall/"
        DESTINATION lib/coasm)

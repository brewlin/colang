set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -g -w -fno-builtin -nostdlib")
aux_source_directory(. srcs)

add_library(crt ${srcs})
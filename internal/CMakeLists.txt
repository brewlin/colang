set(CMAKE_CXX_COMPILER "clang++")

aux_source_directory(. srcs)

add_library(internal ${srcs})
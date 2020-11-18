set(CMAKE_CXX_COMPILER "gcc")

add_definitions("-g -Wall")

aux_source_directory(. srcs)

add_library(internal ${srcs})
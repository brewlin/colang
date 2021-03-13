include_directories(../include ../http)

aux_source_directory(. dir_src)

add_library(core ${dir_src})
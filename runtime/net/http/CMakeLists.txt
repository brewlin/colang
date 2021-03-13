include_directories(. ../include)

aux_source_directory(. dir_src)

add_library(http ${dir_src})
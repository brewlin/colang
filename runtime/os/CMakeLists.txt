aux_source_directory(. dir_src)

add_library(os ${dir_src})

INSTALL(TARGETS os
        ARCHIVE DESTINATION lib/colib)

include_directories(../include)

aux_source_directory(. dir_src)

add_library(event ${dir_src})

INSTALL(TARGETS event
        ARCHIVE DESTINATION lib/colib)

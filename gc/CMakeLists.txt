enable_language(ASM)

aux_source_directory(. srcs)

add_library(gc ${srcs} root.s)

INSTALL(TARGETS gc
        ARCHIVE DESTINATION lib/colib)

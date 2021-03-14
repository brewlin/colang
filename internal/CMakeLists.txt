set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -static -w -fno-builtin -nostdlib")
aux_source_directory(. srcs)

add_library(internal ${srcs})

INSTALL(TARGETS internal
        ARCHIVE DESTINATION lib/colib)

project(demo)

add_definitions("-Wall -g")

include_directories(./include)

add_subdirectory(./core)
add_subdirectory(./event)
add_subdirectory(./http)

add_executable(demo main.c)

target_link_libraries(demo 
                      core http 
                      event core
                      http)
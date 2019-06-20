cmake_minimum_required(VERSION 3.8)
project(zappy)

set(CMAKE_C_COMPILER gcc)
set(CMAKE_C_FLAGS "-fms-extensions")

file(
        GLOB_RECURSE
        source_files
        server_src/*.c
        server_src/*.h
)

file(
        GLOB_RECURSE
        graphic_sources
        graphical_client/*.cpp
        graphical_client/*.hpp
)

include_directories(
        ./graphical_client
        ./server_src/include
)

add_executable(
        zappy_ai
        ${source_files}
)

add_executable(
        zappy_graphic
        ${graphic_sources}
)

target_link_libraries(zappy_ai -lm)

cmake_minimum_required(VERSION 3.8)
project(zappy)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_COMPILER clang)
set(CMAKE_C_FLAGS "-fms-extensions -fblocks")

file(
        GLOB_RECURSE
        source_files
        server_src/*.c
        server_src/*.h
)

include_directories(
        ./server_src/include
)

add_executable(
        ${PROJECT_NAME}
        ${source_files}
)

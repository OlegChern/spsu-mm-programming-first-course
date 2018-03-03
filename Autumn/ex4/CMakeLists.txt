cmake_minimum_required(VERSION 3.8)
project(ex4)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(ex4 ${SOURCE_FILES})

target_link_libraries(ex4 m)
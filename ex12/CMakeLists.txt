cmake_minimum_required(VERSION 3.8)
project(ex12)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c)
add_executable(ex12 ${SOURCE_FILES})

target_link_libraries(ex12 m)
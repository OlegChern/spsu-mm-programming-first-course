cmake_minimum_required(VERSION 3.8)
project(task3)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES Triangle.c scan_pos_nums.c scan_pos_nums.h)
add_executable(task3 ${SOURCE_FILES})

target_link_libraries(task3 m)

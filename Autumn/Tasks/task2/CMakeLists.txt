cmake_minimum_required(VERSION 3.8)
project(task2)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES PythagoreanTriple.c scan_pos_nums.c scan_pos_nums.h)
add_executable(task2 ${SOURCE_FILES})

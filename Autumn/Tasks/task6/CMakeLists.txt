cmake_minimum_required(VERSION 3.8)
project(task6)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES file_sort.c prog_work_time.c prog_work_time.h)
add_executable(task6 ${SOURCE_FILES})

cmake_minimum_required(VERSION 3.8)
project(ex8)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c util.h sobel.c gauss.c other.c bmp.c)
add_executable(ex8 ${SOURCE_FILES})

target_link_libraries(ex8 m)
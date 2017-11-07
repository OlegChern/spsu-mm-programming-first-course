cmake_minimum_required(VERSION 3.8)
project(ex7)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c header.h)
add_executable(ex7 ${SOURCE_FILES})
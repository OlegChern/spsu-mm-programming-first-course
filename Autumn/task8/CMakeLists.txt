cmake_minimum_required(VERSION 3.8)
project(task8)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.c colours.h colours.c)

add_executable(junk ${SOURCE_FILES})
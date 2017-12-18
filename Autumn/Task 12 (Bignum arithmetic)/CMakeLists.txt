cmake_minimum_required(VERSION 3.8)
project(Task_12__Bignum_arithmetic_)

set(CMAKE_C_STANDARD 11)

set(SOURCE_FILES sources/main.c sources/vector.c headers/vector.h sources/bigint.c headers/bigint.h sources/errors.c headers/errors.h)
add_executable(Task_12__Bignum_arithmetic_ ${SOURCE_FILES})
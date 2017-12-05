cmake_minimum_required(VERSION 3.8)
project(task12)

set(CMAKE_C_STANDARD 99)

set(SOURCE_FILES main.c linkedList.c linkedList.h endlessInteger.c endlessInteger.h util.c util.h)
add_executable(task12 ${SOURCE_FILES})
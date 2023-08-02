cmake_minimum_required(VERSION 3.25)
project(NumericalMath C)

set(CMAKE_C_STANDARD 11)

include_directories(include src)
file(GLOB_RECURSE SOURCES src/*.c)

add_library(NumericalMath ${SOURCES})

add_executable(Numericalmath main.c ${SOURCES})
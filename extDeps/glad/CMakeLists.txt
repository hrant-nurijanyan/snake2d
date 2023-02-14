cmake_minimum_required(VERSION 3.22.1)
project(glad C)

set(CMAKE_C_STANDARD 99)

add_library(glad glad.c)

target_include_directories(glad PRIVATE include)

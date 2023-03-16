cmake_minimum_required(VERSION 3.21)
project(C-Templates C)

set(CMAKE_C_STANDARD 17)

add_executable(C-Templates main.c types.h list_test.h list_test.c)
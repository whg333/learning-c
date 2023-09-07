cmake_minimum_required(VERSION 3.21)
project(whg_c C)

set(CMAKE_C_STANDARD 99)

add_executable(whg_c main.c)

add_executable(test hard_way/test.c hard_way)
add_executable(ex1 hard_way/ex1.c)
add_executable(ex10_1 hard_way/ex10_1.c)
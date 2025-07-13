cmake_minimum_required(VERSION 3.27)
project(VLVector C)

set(CMAKE_C_STANDARD 11)

add_executable(VLVector main.c
        vl_vector.c
        vl_vector.h)

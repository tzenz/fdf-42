cmake_minimum_required(VERSION 3.15)
project(fdf C)

set(CMAKE_C_STANDARD 11)

include_directories(.)

add_executable(fdf
        drawline.c
        fdf.h
        readfile.c)

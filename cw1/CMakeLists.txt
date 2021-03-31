cmake_minimum_required(VERSION 2.8)

project(cw1)

set( CMAKE_BUILD_TYPE Debug)

set(CMAKE_C_FLAGS "-fdump-rtl-expand")


add_executable(cw1 main.c manager.c user.c)



cmake_minimum_required(VERSION 2.8.4)
project(na_prj_3_im)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c99")

set(SOURCE_FILES main.c)
add_executable(na_prj_3_im ${SOURCE_FILES})
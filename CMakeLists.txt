cmake_minimum_required(VERSION 3.15)

project(cstd C)
set(CMAKE_C_STANDARD 11)

add_subdirectory(cstd)
if(test)
    add_subdirectory(test)
endif()
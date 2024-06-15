cmake_minimum_required(VERSION 3.29)
project(timestamp_generator)

set(CMAKE_CXX_STANDARD 23)

add_executable(timestamp_generator main.cpp
        IDGenerator.cpp
        IDGenerator.h)

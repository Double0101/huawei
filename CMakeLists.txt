cmake_minimum_required(VERSION 3.9)
project(sdk_gcc)

set(CMAKE_CXX_STANDARD 11)

add_executable(sdk_gcc
        ecs/lib/lib_io.h
        ecs/lib/lib_time.h
        ecs/ecs.cpp
        ecs/io.cpp
        ecs/predict.cpp
        ecs/predict.h)

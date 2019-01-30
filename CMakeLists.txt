cmake_minimum_required(VERSION 3.13)
project(nelder_mid_optimization)

set(CMAKE_CXX_STANDARD 11)

add_executable(nelder_mid_optimization
        main.cpp
        nma.h
        nma.cpp
        point.h
        point.cpp
        types.h
)
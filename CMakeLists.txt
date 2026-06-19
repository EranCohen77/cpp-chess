cmake_minimum_required(VERSION 4.0)
project(cpp_chess)

set(CMAKE_CXX_STANDARD 17)

include_directories(.)

add_executable(cpp_chess
        Move.cpp
        Move.h
        Move.h)

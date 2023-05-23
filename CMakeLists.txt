cmake_minimum_required(VERSION 3.21)
project(DA_project_2)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(DA_project_2
        Graph.cpp
        Graph.h
        Node_Edge.cpp
        Node_Edge.h
        Menu.cpp
        Menu.h
        Algorithms.cpp
        main.cpp)

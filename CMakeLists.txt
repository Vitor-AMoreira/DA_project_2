cmake_minimum_required(VERSION 3.25)
project(Project2)

set(CMAKE_CXX_STANDARD 17)

add_executable( Project2
                src/main.cpp
                src/Graph.h
                src/Menu.cpp
                src/Menu.h
                src/TSPAlgorithms.cpp)

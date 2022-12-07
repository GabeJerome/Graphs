cmake_minimum_required(VERSION 3.23)
project(Graphs)

set(CMAKE_CXX_STANDARD 14)

add_executable(Graphs main.cpp myGraph.cpp myGraph.h Graphs.h testCases.cpp functions.cpp)

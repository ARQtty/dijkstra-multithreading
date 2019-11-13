cmake_minimum_required(VERSION 3.15)
project(dijkstra_effective)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -pthread")

add_executable(dijkstra_effective main.cpp Timer.cpp Timer.h GraphReader.cpp GraphReader.h dijkstra.h)

add_library(Timer SHARED Timer.cpp Timer.h)


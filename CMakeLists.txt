cmake_minimum_required(VERSION 3.23)
project(TSP)

set(CMAKE_CXX_STANDARD 14)

add_executable(TSP main.cpp bfs.h Uniform_cost_search.h A_star.h)

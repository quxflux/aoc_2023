cmake_minimum_required(VERSION 3.21)

project(aoc_2023 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

include(cmake/CPM.cmake)

add_executable(aoc_2023_01 src/day_01/main.cpp)
add_executable(aoc_2023_02 src/day_02/main.cpp)
add_executable(aoc_2023_03 src/day_03/main.cpp)
add_executable(aoc_2023_04 src/day_04/main.cpp)

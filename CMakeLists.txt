cmake_minimum_required(VERSION 3.21)

project(aoc_2023 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

foreach(day RANGE 24)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/day_${day})
        add_executable(aoc_2023_${day} src/day_${day}/main.cpp)
    elseif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/day_0${day})
        add_executable(aoc_2023_0${day} src/day_0${day}/main.cpp)
    endif ()
endforeach()

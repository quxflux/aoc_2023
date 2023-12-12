cmake_minimum_required(VERSION 3.21)

project(aoc_2023 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_EXTENSIONS OFF)

foreach(day RANGE 24)
    if (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/day_${day})
        SET(PROJECT_NAME_${day} aoc_2023_${day})
        SET(PROJECT_DIR_${day} src/day_${day})
    elseif (EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/src/day_0${day})
        SET(PROJECT_NAME_${day} aoc_2023_0${day})
        SET(PROJECT_DIR_${day} src/day_0${day})
    endif ()

    if (DEFINED PROJECT_NAME_${day})
        SET(EXECUTABLE ${PROJECT_NAME_${day}})

        file(GLOB SRC_FILES ${PROJECT_DIR_${day}}/*.cpp ${PROJECT_DIR_${day}}/*.h)
        add_executable(${EXECUTABLE} ${SRC_FILES}
                src/day_10/map.h)
        target_include_directories(${EXECUTABLE} PRIVATE src/common)

        if (APPLE)
            # better debug data visualizer on OSX with CLion
            target_compile_options(${EXECUTABLE} PRIVATE -gdwarf-3)
        endif()
    endif()
endforeach()

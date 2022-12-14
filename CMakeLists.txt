cmake_minimum_required(VERSION 3.24)
project(AdventOfCode)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    if(CMAKE_CXX_COMPILER_VERSION VERSION_LESS "11.0")
        message(FATAL_ERROR "Insufficient gcc version")
    endif()
endif()

add_executable(
        ${PROJECT_NAME}

        main.cpp
        tasks/Day1.hpp
        tasks/Day2.hpp
        tasks/Day3.hpp
        TaskBase.hpp
        tasks/Day4.hpp
        tasks/Day5.hpp
        tasks/Day6.hpp
        tasks/Day7.hpp
        tasks/Day8.hpp
        tasks/Day9.hpp
        tasks/Day11.hpp tasks/Day12.hpp tasks/Day13.hpp tasks/Day14.hpp tasks/Day15.hpp)

target_include_directories(    ${PROJECT_NAME}
        PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

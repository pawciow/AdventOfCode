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
        FirstTask.hpp
        SecondTask.hpp
        TaskThree.hpp
        TaskBase.hpp
        TaskFour.hpp
        TaskFive.hpp
        TaskSix.hpp TaskSeven.hpp TaskEight.hpp)

target_include_directories(    ${PROJECT_NAME}
        PUBLIC
        "${PROJECT_BINARY_DIR}"
        )

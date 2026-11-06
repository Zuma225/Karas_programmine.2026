cmake_minimum_required(VERSION 3.16)

project(lab-06 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(lab-06 main.cpp)

if(MSVC)
    target_compile_options(lab-06 PRIVATE /W4)
else()
    target_compile_options(lab-06 PRIVATE -Wall -Wextra -Wpedantic)
endif()
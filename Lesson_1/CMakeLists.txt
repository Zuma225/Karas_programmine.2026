cmake_minimum_required(VERSION 3.16)

project(lab-01 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


add_executable(lab-01 main.cpp)

if(MSVC)
    target_compile_options(lab-01 PRIVATE /W4)
else()
    target_compile_options(lab-01 PRIVATE -Wall -Wextra -Wpedantic)
endif()
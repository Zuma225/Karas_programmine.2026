cmake_minimum_required(VERSION 3.16)
project(lab04 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# Все .cpp, участвующие в сборке цели, перечислены явно
add_executable(lab04 main.cpp distance.cpp)

if (WIN32)
    target_compile_definitions(lab04 PRIVATE NOMINMAX)
endif()
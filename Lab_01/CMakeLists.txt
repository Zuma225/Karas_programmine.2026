cmake_minimum_required(VERSION 3.16)
project(lab17 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Предупреждения
if (MSVC)
    add_compile_options(/W4 /utf-8)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_executable(lab17 main.cpp)

# Чтобы русский текст корректно выводился в Windows-консоли
if (WIN32)
    target_compile_definitions(lab17 PRIVATE NOMINMAX)
endif()
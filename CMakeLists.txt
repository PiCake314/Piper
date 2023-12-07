cmake_minimum_required(VERSION 3.15)
project(Piper)
set(CMAKE_CXX_STANDARD 20)
add_compile_options(-std=c++20 -Wall -Wextra -Wpedantic -Werror -O0)


set(SOURCE_FILES main.cpp)

add_executable(Piper ${SOURCE_FILES})
cmake_minimum_required(VERSION 3.10)
project(yabi)

set(CMAKE_C_STANDARD 17)

add_executable( yabi
        interpreter.cpp
        src/input_validation.cpp
        src/memory_management.cpp
        src/stack.cpp
        src/pass_one.cpp
        src/pass_two.cpp
)

target_include_directories(yabi PRIVATE include)
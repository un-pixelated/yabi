cmake_minimum_required(VERSION 3.10)
project(yabi)

set(CMAKE_C_STANDARD 17)

add_executable( yabi
        interpreter.c
        src/input_validation.c
        src/memory_management.c
        src/stack.c
        src/pass_one.c
        src/pass_two.c
)

target_include_directories(yabi PRIVATE include)
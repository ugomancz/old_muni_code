cmake_minimum_required(VERSION 3.17)
project(t2)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0")

add_executable(complex complex.cpp)
add_executable(natural_test natural_test.cpp)
add_executable(machine machine.cpp)
add_executable(natural natural.cpp)
add_executable(parser parser.cpp)
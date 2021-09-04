cmake_minimum_required(VERSION 3.17)
project(t1)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)
add_executable(cellular cellular.cpp)
add_executable(reversi reversi.cpp)
add_executable(magic magic.cpp)
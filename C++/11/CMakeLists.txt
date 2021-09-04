cmake_minimum_required(VERSION 3.20)
project(11)

set(CMAKE_CXX_STANDARD 17)
add_compile_options(-Wall -Wextra -pedantic)

add_executable(g1_seq g1_seq.cpp)
add_executable(g2_filter g2_filter.cpp)
add_executable(g3_zip g3_zip.cpp)
add_executable(g4_nibble g4_nibble.cpp)
add_executable(g5_tree g5_tree.cpp)
add_executable(g6_scan g6_scan.cpp)